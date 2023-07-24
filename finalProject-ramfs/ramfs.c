#include "ramfs.h"
/* modify this file freely */
#include <string.h>
#include <stdlib.h>

typedef struct node {
    enum {
        FILE_NODE, DIR_NODE
    } type;
    struct node *first_child;
    struct node *last_child;
    struct node *next_sibling;
    void *content;
    int nrde;
    int size;
    char *name;
} node;

typedef struct FD {
    off_t offset;
    int flags;
    node *f;
    enum {
        FILE_FD, DIR_FD
    } type;
} FD;

node root;
FD Fd[4096];
int IsOccupied[4096];

/*
 * O_APPEND 02000 十进制：1024
 * O_CREAT 0100 十进制：64
 * O_TRUNC 01000 十进制：512
 * O_RDONLY 00 十进制：0
 * O_WRONLY 01 十进制：1
 * O_RDWR 02 十进制：2
 *
 * O_APPEND | O_CREAT = 1088 legal
 * O_APPEND | O_TRUNC = 1536  legal
 * O_APPEND | O_WRONLY = 1025 legal
 * O_APPEND | O_RDWR = 1026 legal
 * O_CREAT | O_TRUNC = 576 legal
 * O_CREAT | O_WRONLY = 65 legal
 * O_CREAT | O_RDWR = 66 legal
 * O_TRUNC | O_WRONLY = 513 legal
 * O_TRUNC | O_RDWR = 514 legal
 * O_WRONLY | O_RDWR = 3 illegal
 *
 * O_APPEND | O_CREAT | O_TRUNC = 1600 can't write
 * O_APPEND | O_CREAT | O_WRONLY = 1089 can't read
 * O_APPEND | O_CREAT | O_RDWR = 1090
 * O_APPEND | O_TRUNC | O_WRONLY = 1537 can't read
 * O_APPEND | O_TRUNC | O_RDWR = 1538
 * O_APPEND | O_WRONLY | O_RDWR = 1027  can't read
 * O_CREAT | O_TRUNC | O_WRONLY = 577  can't read
 * O_CREAT | O_TRUNC | O_RDWR = 578
 * O_CREAT | O_WRONLY | O_RDWR = 67  can't read
 * O_TRUNC | O_WRONLY | O_RDWR = 515  can't read
 *
 * O_APPEND | O_CREAT | O_TRUNC | O_WRONLY = 1601  can't read
 * O_APPEND | O_TRUNC | O_WRONLY | O_RDWR = 1539  can't read
 * O_CREAT | O_TRUNC | O_WRONLY | O_RDWR = 579  can't read
 * O_APPEND | O_CREAT | O_WRONLY | O_RDWR = 1091  can't read
 * O_APPEND | O_CREAT | O_TRUNC | O_RDWR = 1602
 *
 * O_APPEND | O_CREAT | O_TRUNC | O_WRONLY | O_RDWR = 1603 can't read
 */

int IsLegalInLength(const char *pathname) {//pass the simplified pathname
    int len = (int) strlen(pathname);
    int count = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (pathname[i] != '/') {
            count++;
            if (count > 32) {
                return 0;
            }
        } else {
            count = 0;
        }
        if ((pathname[i] < 'a' || pathname[i] > 'z')
            && (pathname[i] < 'A' || pathname[i] > 'Z')
            && (pathname[i] < '0' || pathname[i] > '9')
            && (pathname[i] != '.')
            && (pathname[i] != '/')) {
            return 0;
        }
    }
    return 1;
}

node *search(const char *simplify, node *location);

node *search_sibling(const char *simplify, node *location) {
    node *p = location;
    while (p != NULL) {
        if (strcmp(p->name, simplify) == 0) {
            return p;
        }
        p = p->next_sibling;
    }
    return NULL;
}

node *search_child(const char *simplify, node *location) {
    if (location->first_child == NULL) {
        return NULL;
    }
    return search(simplify, location->first_child);
}

node *search(const char *simplify, node *location) {
    if (strcmp(location->name, simplify) == 0) {
        return location;
    } else if (location->type == FILE_NODE) {
        if (location->next_sibling == NULL) {
            return NULL;
        } else {
            node *record = search_sibling(simplify, location->next_sibling);
            if (record != NULL) {
                return record;
            }
            node *q = location->next_sibling;
            int len1 = (int) strlen(simplify);
            while (q != NULL) {
                if (q->type == DIR_NODE) {
                    int len = (int) strlen(q->name);
                    if (len <= len1 - 1) {
                        if (strncmp(q->name, simplify, len) == 0) {
                            node *record2 = search_child(simplify, q);
                            if (record2 != NULL) {
                                return record2;
                            }
                        }
                    }
                }
                q = q->next_sibling;
            }
            return NULL;
        }
    } else if (location->type == DIR_NODE) {
        int len1 = (int) strlen(simplify);
        int len2 = (int) strlen(location->name);
        if (len2 + 1 <= len1) {
            if (strncmp(location->name, simplify, len2) == 0) {
                node *record1 = search_child(simplify, location);
                if (record1 != NULL) {
                    return record1;
                }
            }
        }
        if (location->next_sibling == NULL) {
            return NULL;
        }
        node *record = search_sibling(simplify, location->next_sibling);
        if (record != NULL) {
            return record;
        }
        node *q = location->next_sibling;
        while (q != NULL) {
            if (q->type == DIR_NODE) {
                int len3 = (int) strlen(q->name);
                if (len3 + 1 <= len1) {
                    if (strncmp(q->name, simplify, len3) == 0) {
                        node *record2 = search_child(simplify, q);
                        if (record2 != NULL) {
                            return record2;
                        }
                    }
                }
            }
            q = q->next_sibling;
        }
        return NULL;
    }
}


int ropen(const char *pathname, int flags) {
    int len = (int) strlen(pathname);
    if (len > 1024) {
        return -1;
    }
    char *simplify = (char *) malloc((len + 1) * sizeof(char));
    int count = 0;
    for (int i = 0; i < len - 1; i++) {
        if ((*(pathname + i) == '/' && *(pathname + i + 1) != '/') || *(pathname + i) != '/') {
            simplify[count] = *(pathname + i);
            count++;
        }
    }
    int end = 0;
    if (*(pathname + len - 1) != '/') {
        simplify[count] = *(pathname + len - 1);
        count++;
        simplify[count] = 0;
    } else {
        if (len == 1) {
            simplify[count] = *(pathname + len - 1);
            count++;
            simplify[count] = 0;
            end = 1;
        } else {
            end = 1;
            simplify[count] = 0;
        }
    }
    if (IsLegalInLength(simplify) == 0) {
        free(simplify);
        return -1;
    }
    node *location = &root;
    node *find = search(simplify, location);
    if (find == NULL) {
        int len = (int) strlen(simplify);
        char *father = (char *) malloc((len + 1) * sizeof(char));
        strcpy(father, simplify);
        for (int i = len - 1; i >= 0; i--) {
            if (father[i] == '/') {
                if (i != 0) {
                    father[i] = 0;
                    break;
                } else {
                    father[1] = 0;
                }
            }
        }
        node *father_ptr = search(father, location);
        free(father);
        if (father_ptr == NULL) {
            free(simplify);
            return -1;
        } else if (father_ptr->type == FILE_NODE) {
            free(simplify);
            return -1;
        } else if (father_ptr->type == DIR_NODE) {
            if ((flags == O_CREAT)
                || (flags == (O_CREAT | O_WRONLY))
                || (flags == (O_CREAT | O_RDWR))
                || (flags == (O_APPEND | O_CREAT))
                || (flags == (O_CREAT | O_TRUNC))
                || (flags == (O_APPEND | O_CREAT | O_TRUNC))
                || (flags == (O_APPEND | O_CREAT | O_WRONLY))
                || (flags == (O_APPEND | O_CREAT | O_RDWR))
                || (flags == (O_CREAT | O_TRUNC | O_WRONLY))
                || (flags == (O_CREAT | O_TRUNC | O_RDWR))
                || (flags == (O_CREAT | O_WRONLY | O_RDWR))
                || (flags == (O_APPEND | O_CREAT | O_TRUNC | O_WRONLY))
                || (flags == (O_CREAT | O_TRUNC | O_WRONLY | O_RDWR))
                || (flags == (O_APPEND | O_CREAT | O_WRONLY | O_RDWR))
                || (flags == (O_APPEND | O_CREAT | O_TRUNC | O_RDWR))
                || (flags == (O_APPEND | O_CREAT | O_TRUNC | O_WRONLY | O_RDWR))) {
                father_ptr->nrde++;
                node *new_file = (node *) malloc(sizeof(node));
                new_file->type = FILE_NODE;
                new_file->name = simplify;
                new_file->size = 0;
                new_file->content = NULL;
                new_file->next_sibling = NULL;
                if (father_ptr->last_child == NULL) {
                    father_ptr->first_child = new_file;
                    father_ptr->last_child = new_file;
                } else {
                    father_ptr->last_child->next_sibling = new_file;
                    father_ptr->last_child = father_ptr->last_child->next_sibling;
                }
                for (int i = 0; i < 4096; i++) {
                    if (IsOccupied[i] == 0) {
                        Fd[i].type = FILE_FD;
                        Fd[i].flags = flags;
                        Fd[i].f = new_file;
                        Fd[i].offset = 0;
                        IsOccupied[i] = 1;
                        return i;
                    }
                }
            } else {
                free(simplify);
                return -1;
            }
        }
    } else if (find->type == FILE_NODE) {
        free(simplify);
        if (end) {
            return -1;
        } else {
            if ((flags == O_CREAT)
                || (flags == O_RDONLY)
                || (flags == O_RDWR)
                || (flags == O_WRONLY)
                || (flags == (O_CREAT | O_WRONLY))
                || (flags == (O_CREAT | O_RDWR))
                || (flags == (O_CREAT | O_WRONLY | O_RDWR))) {
                for (int i = 0; i < 4096; i++) {
                    if (IsOccupied[i] == 0) {
                        Fd[i].type = FILE_FD;
                        Fd[i].f = find;
                        Fd[i].flags = flags;
                        Fd[i].offset = 0;
                        IsOccupied[i] = 1;
                        return i;
                    }
                }
            } else if (flags == (O_WRONLY | O_RDWR)) {
                return -1;
            } else if ((flags == O_APPEND)
                       || (flags == (O_APPEND | O_CREAT))
                       || (flags == (O_APPEND | O_WRONLY))
                       || (flags == (O_APPEND | O_RDWR))
                       || (flags == (O_APPEND | O_CREAT | O_WRONLY))
                       || (flags == (O_APPEND | O_CREAT | O_RDWR))
                       || (flags == (O_APPEND | O_WRONLY | O_RDWR))
                       || (flags == (O_APPEND | O_CREAT | O_WRONLY | O_RDWR))) {
                for (int i = 0; i < 4096; i++) {
                    if (IsOccupied[i] == 0) {
                        Fd[i].type = FILE_FD;
                        Fd[i].f = find;
                        Fd[i].flags = flags;
                        Fd[i].offset = find->size;
                        IsOccupied[i] = 1;
                        return i;
                    }
                }
            } else if ((flags == O_TRUNC)
                       || (flags == (O_CREAT | O_TRUNC))
                       || (flags == (O_APPEND | O_TRUNC))
                       || (flags == (O_APPEND | O_CREAT | O_TRUNC))) {
                for (int i = 0; i < 4096; i++) {
                    if (IsOccupied[i] == 1) {
                        if ((Fd[i].f == find) &&
                            ((Fd[i].flags == O_WRONLY)
                             || (Fd[i].flags == O_RDWR)
                             || (Fd[i].flags == (O_APPEND | O_WRONLY))
                             || (Fd[i].flags == (O_APPEND | O_RDWR))
                             || (Fd[i].flags == (O_CREAT | O_WRONLY))
                             || (Fd[i].flags == (O_CREAT | O_RDWR))
                             || (Fd[i].flags == (O_TRUNC | O_WRONLY))
                             || (Fd[i].flags == (O_TRUNC | O_RDWR))
                             || (Fd[i].flags == (O_APPEND | O_CREAT | O_WRONLY))
                             || (Fd[i].flags == (O_APPEND | O_CREAT | O_RDWR))
                             || (Fd[i].flags == (O_APPEND | O_TRUNC | O_WRONLY))
                             || (Fd[i].flags == (O_APPEND | O_TRUNC | O_RDWR))
                             || (Fd[i].flags == (O_APPEND | O_WRONLY | O_RDWR))
                             || (Fd[i].flags == (O_CREAT | O_TRUNC | O_WRONLY))
                             || (Fd[i].flags == (O_CREAT | O_TRUNC | O_RDWR))
                             || (Fd[i].flags == (O_CREAT | O_WRONLY | O_RDWR))
                             || (Fd[i].flags == (O_TRUNC | O_WRONLY | O_RDWR))
                             || (Fd[i].flags == (O_APPEND | O_CREAT | O_TRUNC | O_WRONLY))
                             || (Fd[i].flags == (O_APPEND | O_TRUNC | O_WRONLY | O_RDWR))
                             || (Fd[i].flags == (O_CREAT | O_TRUNC | O_WRONLY | O_RDWR))
                             || (Fd[i].flags == (O_APPEND | O_CREAT | O_WRONLY | O_RDWR))
                             || (Fd[i].flags == (O_APPEND | O_CREAT | O_TRUNC | O_RDWR))
                             || (Fd[i].flags == (O_APPEND | O_CREAT | O_TRUNC | O_WRONLY | O_RDWR)))) {
                            find->content = realloc(find->content, 0);
                            find->size = 0;
                            break;
                        }
                    }
                }
                for (int i = 0; i < 4096; i++) {
                    if (IsOccupied[i] == 0) {
                        Fd[i].f = find;
                        Fd[i].type = FILE_FD;
                        Fd[i].flags = flags;
                        if ((flags == O_TRUNC)
                            || (flags == (O_CREAT | O_TRUNC))) {
                            Fd[i].offset = 0;
                        } else {
                            Fd[i].offset = find->size;
                        }
                        IsOccupied[i] = 1;
                        return i;
                    }
                }
            } else if ((flags == (O_TRUNC | O_WRONLY))
                       || (flags == (O_TRUNC | O_RDWR))
                       || (flags == (O_APPEND | O_TRUNC | O_WRONLY))
                       || (flags == (O_APPEND | O_TRUNC | O_RDWR))
                       || (flags == (O_CREAT | O_TRUNC | O_WRONLY))
                       || (flags == (O_CREAT | O_TRUNC | O_RDWR))
                       || (flags == (O_TRUNC | O_WRONLY | O_RDWR))
                       || (flags == (O_APPEND | O_CREAT | O_TRUNC | O_WRONLY))
                       || (flags == (O_APPEND | O_TRUNC | O_WRONLY | O_RDWR))
                       || (flags == (O_CREAT | O_TRUNC | O_WRONLY | O_RDWR))
                       || (flags == (O_APPEND | O_CREAT | O_TRUNC | O_RDWR))
                       || (flags == (O_APPEND | O_CREAT | O_TRUNC | O_WRONLY | O_RDWR))) {
                find->content = realloc(find->content, 0);
                find->size = 0;
                for (int i = 0; i < 4096; i++) {
                    if (IsOccupied[i] == 0) {
                        Fd[i].type = FILE_FD;
                        Fd[i].f = find;
                        Fd[i].flags = flags;
                        Fd[i].offset = 0;
                        IsOccupied[i] = 1;
                        return i;
                    }
                }
            }
        }
    } else if (find->type == DIR_NODE) {
        free(simplify);
        for (int i = 0; i < 4096; i++) {
            if (IsOccupied[i] == 0) {
                Fd[i].type = DIR_FD;
                Fd[i].f = find;
                IsOccupied[i] = 1;
                return i;
            }
        }
    }
}

int rclose(int fd) {
    extern node root;
    extern FD Fd[4096];
    extern int IsOccupied[4096];
    if (fd < 0) {
        return -1;
    } else if (IsOccupied[fd] == 1) {
        IsOccupied[fd] = 0;
        return 0;
    } else {
        return -1;
    }
}

ssize_t rwrite(int fd, const void *buf, size_t count) {
    extern node root;
    extern FD Fd[4096];
    extern int IsOccupied[4096];
    if (fd < 0) {
        return -1;
    } else if (IsOccupied[fd] == 0) {
        return -1;
    } else if (Fd[fd].type == DIR_FD) {
        return -1;
    } else if ((Fd[fd].flags != O_WRONLY)
               && (Fd[fd].flags != O_RDWR)
               && (Fd[fd].flags != (O_APPEND | O_WRONLY))
               && (Fd[fd].flags != (O_APPEND | O_RDWR))
               && (Fd[fd].flags != (O_CREAT | O_WRONLY))
               && (Fd[fd].flags != (O_CREAT | O_RDWR))
               && (Fd[fd].flags != (O_TRUNC | O_WRONLY))
               && (Fd[fd].flags != (O_TRUNC | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_CREAT | O_WRONLY))
               && (Fd[fd].flags != (O_APPEND | O_CREAT | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_TRUNC | O_WRONLY))
               && (Fd[fd].flags != (O_APPEND | O_TRUNC | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_WRONLY | O_RDWR))
               && (Fd[fd].flags != (O_CREAT | O_TRUNC | O_WRONLY))
               && (Fd[fd].flags != (O_CREAT | O_TRUNC | O_RDWR))
               && (Fd[fd].flags != (O_CREAT | O_WRONLY | O_RDWR))
               && (Fd[fd].flags != (O_TRUNC | O_WRONLY | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_CREAT | O_TRUNC | O_WRONLY))
               && (Fd[fd].flags != (O_APPEND | O_TRUNC | O_WRONLY | O_RDWR))
               && (Fd[fd].flags != (O_CREAT | O_TRUNC | O_WRONLY | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_CREAT | O_WRONLY | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_CREAT | O_TRUNC | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_CREAT | O_TRUNC | O_WRONLY | O_RDWR))) {
        return -1;
    } else {
        node *file = Fd[fd].f;
        if (Fd[fd].offset <= file->size) {
            if (Fd[fd].offset + count <= file->size) {
                memcpy(file->content + Fd[fd].offset, buf, count);
                Fd[fd].offset += count;
                return count;
            } else {
                file->content = realloc(file->content, Fd[fd].offset + count);
                memcpy(file->content + Fd[fd].offset, buf, count);
                file->size = Fd[fd].offset + count;
                Fd[fd].offset += count;
                return count;
            }
        } else {
            file->content = realloc(file->content, Fd[fd].offset + count);
            memcpy(file->content + Fd[fd].offset, buf, count);
            for (off_t i = file->size; i <= Fd[fd].offset - 1; i++) {
                *(char *) (file->content + i) = '\0';
            }
            file->size = Fd[fd].offset + count;
            Fd[fd].offset += count;
            return count;
        }
    }
}

ssize_t rread(int fd, void *buf, size_t count) {
    extern node root;
    extern FD Fd[4096];
    extern int IsOccupied[4096];
    if (fd < 0) {
        return -1;
    } else if (IsOccupied[fd] == 0) {
        return -1;
    } else if (Fd[fd].type == DIR_FD) {
        return -1;
    } else if ((Fd[fd].flags != O_APPEND)
               && (Fd[fd].flags != O_CREAT)
               && (Fd[fd].flags != O_TRUNC)
               && (Fd[fd].flags != O_RDONLY)
               && (Fd[fd].flags != O_RDWR)
               && (Fd[fd].flags != (O_APPEND | O_CREAT))
               && (Fd[fd].flags != (O_APPEND | O_TRUNC))
               && (Fd[fd].flags != (O_APPEND | O_RDWR))
               && (Fd[fd].flags != (O_CREAT | O_TRUNC))
               && (Fd[fd].flags != (O_CREAT | O_RDWR))
               && (Fd[fd].flags != (O_TRUNC | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_CREAT | O_TRUNC))
               && (Fd[fd].flags != (O_APPEND | O_CREAT | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_TRUNC | O_RDWR))
               && (Fd[fd].flags != (O_CREAT | O_TRUNC | O_RDWR))
               && (Fd[fd].flags != (O_APPEND | O_CREAT | O_TRUNC | O_RDWR))) {
        return -1;
    } else {
        node *file = Fd[fd].f;
        if (Fd[fd].offset + count > file->size) {
            memcpy(buf, file->content + Fd[fd].offset, file->size - Fd[fd].offset);
            off_t record = Fd[fd].offset;
            Fd[fd].offset = file->size;
            return file->size - record;
        } else {
            memcpy(buf, file->content + Fd[fd].offset, count);
            Fd[fd].offset += count;
            return count;
        }
    }
}

off_t rseek(int fd, off_t offset, int whence) {
    extern node root;
    extern FD Fd[4096];
    extern int IsOccupied[4096];
    if (fd < 0) {
        return -1;
    } else if (IsOccupied[fd] == 0) {
        return -1;
    } else if (Fd[fd].type == DIR_FD) {
        return -1;
    } else {
        if (whence == SEEK_SET) {
            if (offset < 0) {
                return -1;
            } else {
                Fd[fd].offset = offset;
                return Fd[fd].offset;
            }
        } else if (whence == SEEK_CUR) {
            if (Fd[fd].offset + offset < 0) {
                return -1;
            } else {
                Fd[fd].offset = Fd[fd].offset + offset;
                return Fd[fd].offset;
            }
        } else if (whence == SEEK_END) {
            node *file = Fd[fd].f;
            if (file->size + offset < 0) {
                return -1;
            } else {
                Fd[fd].offset = file->size + offset;
                return Fd[fd].offset;
            }
        }
    }
}

int rmkdir(const char *pathname) {
    extern node root;
    extern FD Fd[4096];
    extern int IsOccupied[4096];
    int len = (int) strlen(pathname);
    if (len > 1024) {
        return -1;
    }
    char *simplify = (char *) malloc((len + 1) * sizeof(char));
    int count = 0;
    for (int i = 0; i < len - 1; i++) {
        if ((*(pathname + i) == '/' && *(pathname + i + 1) != '/') || *(pathname + i) != '/') {
            simplify[count] = *(pathname + i);
            count++;
        }
    }
    if (*(pathname + len - 1) != '/') {
        simplify[count] = *(pathname + len - 1);
        count++;
        simplify[count] = 0;
    } else {
        if (len == 1) {
            simplify[count] = *(pathname + len - 1);
            count++;
            simplify[count] = 0;
        } else {
            simplify[count] = 0;
        }
    }
    if (IsLegalInLength(simplify) == 0) {
        free(simplify);
        return -1;
    }
    if (search(simplify, &root) != NULL) {
        free(simplify);
        return -1;
    } else {
        int length = (int) strlen(simplify);
        char *father = (char *) malloc((length + 1) * sizeof(char));
        strcpy(father, simplify);
        for (int i = length - 1; i >= 0; i--) {
            if (father[i] == '/') {
                if (i != 0) {
                    father[i] = 0;
                    break;
                } else {
                    father[1] = 0;
                }
            }
        }
        node *father_ptr = search(father, &root);
        free(father);
        if (father_ptr == NULL) {
            free(simplify);
            return -1;
        } else if (father_ptr->type == FILE_NODE) {
            free(simplify);
            return -1;
        } else {
            node *new_dir = (node *) malloc(sizeof(node));
            new_dir->type = DIR_NODE;
            new_dir->nrde = 0;
            new_dir->first_child = NULL;
            new_dir->last_child = NULL;
            new_dir->next_sibling = NULL;
            new_dir->name = simplify;
            father_ptr->nrde++;
            if (father_ptr->last_child == NULL) {
                father_ptr->first_child = new_dir;
                father_ptr->last_child = new_dir;
            } else {
                father_ptr->last_child->next_sibling = new_dir;
                father_ptr->last_child = father_ptr->last_child->next_sibling;
            }
            return 0;
        }
    }
}

int rrmdir(const char *pathname) {
    extern node root;
    extern FD Fd[4096];
    extern int IsOccupied[4096];
    int len = (int) strlen(pathname);
    if (len > 1024) {
        return -1;
    }
    char *simplify = (char *) malloc((len + 1) * sizeof(char));
    int count = 0;
    for (int i = 0; i < len - 1; i++) {
        if ((*(pathname + i) == '/' && *(pathname + i + 1) != '/') || *(pathname + i) != '/') {
            simplify[count] = *(pathname + i);
            count++;
        }
    }
    if (*(pathname + len - 1) != '/') {
        simplify[count] = *(pathname + len - 1);
        count++;
        simplify[count] = 0;
    } else {
        if (len == 1) {
            simplify[count] = *(pathname + len - 1);
            count++;
            simplify[count] = 0;
        } else {
            simplify[count] = 0;
        }
    }
    if (IsLegalInLength(simplify) == 0) {
        free(simplify);
        return -1;
    }
    node *find = search(simplify, &root);
    if (find == NULL) {
        free(simplify);
        return -1;
    } else if (find->type == FILE_NODE) {
        free(simplify);
        return -1;
    } else if (strcmp(find->name, "/") == 0) {
        free(simplify);
        return -1;
    } else if (find->nrde != 0) {
        free(simplify);
        return -1;
    } else {
        int length = (int) strlen(simplify);
        char *father = (char *) malloc((length + 1) * sizeof(char));
        strcpy(father, simplify);
        free(simplify);
        for (int i = length - 1; i >= 0; i--) {
            if (father[i] == '/') {
                if (i != 0) {
                    father[i] = 0;
                    break;
                } else {
                    father[1] = 0;
                }
            }
        }
        node *father_ptr = search(father, &root);
        free(father);
        father_ptr->nrde--;
        node *p = father_ptr->first_child;
        if (p == find) {
            if (p->next_sibling == NULL) {
                father_ptr->first_child = NULL;
                father_ptr->last_child = NULL;
            } else {
                father_ptr->first_child = p->next_sibling;
            }
        } else {
            node *q = p->next_sibling;
            while (q != find) {
                p = q;
                q = q->next_sibling;
            }
            if (q->next_sibling == NULL) {
                father_ptr->last_child = p;
                p->next_sibling = NULL;
            } else {
                p->next_sibling = q->next_sibling;
            }
        }
        free(find->name);
        free(find);
        return 0;
    }
}

int runlink(const char *pathname) {
    extern node root;
    extern FD Fd[4096];
    extern int IsOccupied[4096];
    int len = (int) strlen(pathname);
    if (len > 1024) {
        return -1;
    }
    char *simplify = (char *) malloc((len + 1) * sizeof(char));
    int count = 0;
    for (int i = 0; i < len - 1; i++) {
        if ((*(pathname + i) == '/' && *(pathname + i + 1) != '/') || *(pathname + i) != '/') {
            simplify[count] = *(pathname + i);
            count++;
        }
    }
    int end = 0;
    if (*(pathname + len - 1) != '/') {
        simplify[count] = *(pathname + len - 1);
        count++;
        simplify[count] = 0;
    } else {
        if (len == 1) {
            simplify[count] = *(pathname + len - 1);
            count++;
            simplify[count] = 0;
            end = 1;
        } else {
            end = 1;
            simplify[count] = 0;
        }
    }
    if (IsLegalInLength(simplify) == 0) {
        free(simplify);
        return -1;
    }
    node *find = search(simplify, &root);
    if (find == NULL) {
        free(simplify);
        return -1;
    } else if (find->type == DIR_NODE) {
        free(simplify);
        return -1;
    } else {
        if (end) {
            free(simplify);
            return -1;
        } else {
            int length = (int) strlen(simplify);
            char *father = (char *) malloc((length + 1) * sizeof(char));
            strcpy(father, simplify);
            free(simplify);
            for (int i = length - 1; i >= 0; i--) {
                if (father[i] == '/') {
                    if (i != 0) {
                        father[i] = 0;
                        break;
                    } else {
                        father[1] = 0;
                    }
                }
            }
            node *father_ptr = search(father, &root);
            free(father);
            father_ptr->nrde--;
            node *p = father_ptr->first_child;
            if (p == find) {
                if (p->next_sibling == NULL) {
                    father_ptr->first_child = NULL;
                    father_ptr->last_child = NULL;
                } else {
                    father_ptr->first_child = p->next_sibling;
                }
            } else {
                node *q = p->next_sibling;
                while (q != find) {
                    p = q;
                    q = q->next_sibling;
                }
                if (q->next_sibling == NULL) {
                    p->next_sibling = NULL;
                    father_ptr->last_child = p;
                } else {
                    p->next_sibling = q->next_sibling;
                }
            }
            if (find->content != NULL) {
                free(find->content);
            }
            free(find->name);
            free(find);
            return 0;
        }
    }
}

void init_ramfs() {
    extern node root;
    extern FD Fd[4096];
    extern int IsOccupied[4096];
    root.type = DIR_NODE;
    root.name = "/";
    root.next_sibling = NULL;
    root.first_child = NULL;
    root.last_child = NULL;
    root.nrde = 0;
    for (int i = 0; i < 4096; i++) {
        IsOccupied[i] = 0;
    }
}


