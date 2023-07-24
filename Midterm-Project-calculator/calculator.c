//
// Created by 25378 on 2022/11/28.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

typedef enum {
    FalseCk, TrueCk, ErrorCk
} Check;
enum TokenType {
    VARIABLE, INTEGER, OPERATOR, FLOAT, ERROR
};
typedef struct token {
    enum TokenType type;
    char str[50];
    union {
        int INT_NUM;
        double FLOAT_NUM;
    } val_of_nums;
    int isLoaded_int;
    int isLoaded_double;
    int position;
} Token;

typedef struct value {
    enum {
        INT_val,
        FLOAT_val,
        ERROR_val
    } type;
    union {
        int iVal;
        double fVal;
    } val;
} Value;

typedef struct primary_operator{
    int position;
    char type;
} Op;

typedef struct store_var{
    int isLoaded;
    char str[50];
    int len;
    union {
        int i_val;
        double f_val;
    } value;
    enum {
        INT, DOUBLE
    } type;
} StoreVar;

int convert_to_int(char str[], int len);
double convert_to_double(char str[], int len);
int isVariable(char single_token[], int len);
int isInteger(char single_token[], int len);
int isOperator(char single_token[], int len);
int isFloat(char single_token[], int len);
Check check_parentheses(int l, int r, Token tokens[]);
Check check_minus_operator(int l, int r, Token tokens[]);
Op SrhPrimaryOp(int l, int r, Token tokens[]);
Value eval(int l, int r, Token tokens[]);
Value meetValue(Value v1, Value v2, Op op);
Value evalAssign(int l, int r, Token tokens[]);
void printValue(Value v);
void load(Token var, Value val);

StoreVar variables[200] = {{{0}, 0}};
int num_of_variables = 0;

int main(void) {
    char *s = (char *) malloc(2000 * sizeof(char));
    //get the input
    while (gets(s) != NULL) {
        int len_of_s = (int) strlen(s);
        //Do the lexical analysis
        Token tokens[2000] = {{0, {0}, {0}}};
        //split the string by ' ' and analyse the type and save the tokens to tokens[]
        int len_of_tokens = 0;
        char *single_token = strtok(s, " ");
        int len_of_single_token = (int) strlen(single_token);
        int isLexicalError = 0;
        for (int i = 0; i < len_of_single_token; i++) {
            tokens[len_of_tokens].str[i] = *(single_token + i);
        }
        if (isVariable(tokens[len_of_tokens].str, len_of_single_token)) {
            tokens[len_of_tokens].type = VARIABLE;
            int judge_2 = 0;
            for (int i = 0; i < num_of_variables; i++) {
                int judge = 1;
                if (len_of_single_token != variables[i].len) {
                    judge = 0;
                } else {
                    for (int j = 0; j < variables[i].len; j++) {
                        if (tokens[len_of_tokens].str[j] != variables[i].str[j]) {
                            judge = 0;
                            break;
                        }
                    }
                }
                if (judge) {
                    if (variables[i].isLoaded) {
                        if (variables[i].type == INT) {
                            tokens[len_of_tokens].position = i;
                            tokens[len_of_tokens].isLoaded_int = 1;
                            tokens[len_of_tokens].isLoaded_double = 0;
                            tokens[len_of_tokens].val_of_nums.INT_NUM = variables[i].value.i_val;
                        } else if (variables[i].type == DOUBLE) {
                            tokens[len_of_tokens].position = i;
                            tokens[len_of_tokens].isLoaded_double = 1;
                            tokens[len_of_tokens].isLoaded_int = 0;
                            tokens[len_of_tokens].val_of_nums.FLOAT_NUM = variables[i].value.f_val;
                        }
                        judge_2 = 1;
                        break;
                    } else {
                        tokens[len_of_tokens].position = i;
                        tokens[len_of_tokens].isLoaded_double = 0;
                        tokens[len_of_tokens].isLoaded_int = 0;
                        judge_2 = 1;
                        break;
                    }
                }
            }
            if (judge_2 == 0) {
                for (int i = 0; i < len_of_single_token; i++) {
                    variables[num_of_variables].str[i] = tokens[len_of_tokens].str[i];
                }
                variables[num_of_variables].len = len_of_single_token;
                variables[num_of_variables].isLoaded = 0;
                tokens[len_of_tokens].position = num_of_variables;
                num_of_variables++;
                tokens[len_of_tokens].isLoaded_double = 0;
                tokens[len_of_tokens].isLoaded_int = 0;
            }
        } else if (isInteger(tokens[len_of_tokens].str, len_of_single_token)) {
            tokens[len_of_tokens].type = INTEGER;
            tokens[len_of_tokens].val_of_nums.INT_NUM = convert_to_int(tokens[len_of_tokens].str, len_of_single_token);
        } else if (isOperator(tokens[len_of_tokens].str, len_of_single_token)) {
            tokens[len_of_tokens].type = OPERATOR;
        } else if (isFloat(tokens[len_of_tokens].str, len_of_single_token)) {
            tokens[len_of_tokens].type = FLOAT;
            tokens[len_of_tokens].val_of_nums.FLOAT_NUM = convert_to_double(tokens[len_of_tokens].str,
                                                                            len_of_single_token);
        } else {
            tokens[len_of_tokens].type = ERROR;
            isLexicalError = 1;
        }
        int judge_3 = 1;
        len_of_tokens++;
        if (s + len_of_s == single_token + len_of_single_token) {
            judge_3 = 0;
        } else {
            single_token = strtok(single_token + len_of_single_token + 1, " ");
        }
        if (isLexicalError) {
            printf("Error\n");
        } else {
            while (judge_3) {
                len_of_single_token = (int) strlen(single_token);
                for (int i = 0; i < len_of_single_token; i++) {
                    tokens[len_of_tokens].str[i] = *(single_token + i);
                }
                if (isVariable(tokens[len_of_tokens].str, len_of_single_token)) {
                    tokens[len_of_tokens].type = VARIABLE;
                    int judge_2 = 0;
                    for (int i = 0; i < num_of_variables; i++) {
                        int judge = 1;
                        if (len_of_single_token != variables[i].len) {
                            judge = 0;
                        } else {
                            for (int j = 0; j < variables[i].len; j++) {
                                if (tokens[len_of_tokens].str[j] != variables[i].str[j]) {
                                    judge = 0;
                                    break;
                                }
                            }
                        }
                        if (judge) {
                            if (variables[i].isLoaded) {
                                if (variables[i].type == INT) {
                                    tokens[len_of_tokens].position = i;
                                    tokens[len_of_tokens].isLoaded_int = 1;
                                    tokens[len_of_tokens].isLoaded_double = 0;
                                    tokens[len_of_tokens].val_of_nums.INT_NUM = variables[i].value.i_val;
                                } else if (variables[i].type == DOUBLE) {
                                    tokens[len_of_tokens].position = i;
                                    tokens[len_of_tokens].isLoaded_double = 1;
                                    tokens[len_of_tokens].isLoaded_int = 0;
                                    tokens[len_of_tokens].val_of_nums.FLOAT_NUM = variables[i].value.f_val;
                                }
                                judge_2 = 1;
                                break;
                            } else {
                                tokens[len_of_tokens].position = i;
                                tokens[len_of_tokens].isLoaded_double = 0;
                                tokens[len_of_tokens].isLoaded_int = 0;
                                judge_2 = 1;
                                break;
                            }
                        }
                    }
                    if (judge_2 == 0) {
                        for (int i = 0; i < len_of_single_token; i++) {
                            variables[num_of_variables].str[i] = tokens[len_of_tokens].str[i];
                        }
                        variables[num_of_variables].len = len_of_single_token;
                        variables[num_of_variables].isLoaded = 0;
                        tokens[len_of_tokens].position = num_of_variables;
                        num_of_variables++;
                        tokens[len_of_tokens].isLoaded_double = 0;
                        tokens[len_of_tokens].isLoaded_int = 0;
                    }
                } else if (isInteger(tokens[len_of_tokens].str, len_of_single_token)) {
                    tokens[len_of_tokens].type = INTEGER;
                    tokens[len_of_tokens].val_of_nums.INT_NUM = convert_to_int(tokens[len_of_tokens].str,
                                                                               len_of_single_token);
                } else if (isOperator(tokens[len_of_tokens].str, len_of_single_token)) {
                    tokens[len_of_tokens].type = OPERATOR;
                } else if (isFloat(tokens[len_of_tokens].str, len_of_single_token)) {
                    tokens[len_of_tokens].type = FLOAT;
                    tokens[len_of_tokens].val_of_nums.FLOAT_NUM = convert_to_double(tokens[len_of_tokens].str,
                                                                                    len_of_single_token);
                } else {
                    tokens[len_of_tokens].type = ERROR;
                    isLexicalError = 1;
                    break;
                }
                len_of_tokens++;
                if (s + len_of_s == single_token + len_of_single_token) {
                    judge_3 = 0;
                } else {
                    single_token = strtok(single_token + len_of_single_token + 1, " ");
                }
            }

            if (isLexicalError == 0) {
                printValue(evalAssign(0, len_of_tokens - 1, tokens));
            } else {
                printf("Error\n");
            }
        }
    }
    free(s);
    return 0;
}

int isVariable(char single_token[], int len) {
    int for_judge = 1;
    if (single_token[0] >= '0' && single_token[0] <= '9') {
        for_judge = 0;
    } else {
        for (int i = 0; i < len; i++) {
            if ((single_token[i] < '0' || single_token[i] > '9')
                && (single_token[i] < 'a' || single_token[i] > 'z')
                && (single_token[i] < 'A' || single_token[i] > 'Z')
                && (single_token[i] != '_')) {
                for_judge = 0;
                break;
            }
        }
    }
    return for_judge;
}

int isInteger(char single_token[], int len) {
    int for_judge = 1;
    if (len > 1) {
        if (single_token[0] >= '1' && single_token[0] <= '9') {
            for (int i = 1; i < len; i++) {
                if (single_token[i] < '0' || single_token[i] > '9') {
                    for_judge = 0;
                    break;
                }
            }
        } else {
            for_judge = 0;
        }
    } else if (len == 1) {
        if (single_token[0] >= '0' && single_token[0] <= '9') {
            for_judge = 1;
        } else {
            for_judge = 0;
        }
    }
    return for_judge;
}

int isOperator(char single_token[], int len) {
    int for_judge = 0;
    if (len == 1 && (single_token[0] == '+'
                     || single_token[0] == '-'
                     || single_token[0] == '*'
                     || single_token[0] == '/'
                     || single_token[0] == '('
                     || single_token[0] == ')'
                     || single_token[0] == '=')) {
        for_judge = 1;
    }
    return for_judge;
}

int isFloat(char single_token[], int len) {
    int for_judge = 1;
    if ((single_token[0] == '.') || (single_token[len - 1] == '.') || len < 3) {
        for_judge = 0;
    } else if (single_token[0] == '0' && single_token[1] != '.') {
        for_judge = 0;
    } else {
        int count = 0;
        for (int i = 0; i < len; i++) {
            if (single_token[i] == '.') {
                count++;
            } else if (single_token[i] > '9' || single_token[i] < '0') {
                for_judge = 0;
                break;
            }
        }
        if (for_judge && count != 1) {
            for_judge = 0;
        }
    }
    return for_judge;
}

int convert_to_int(char str[], int len) {
    int num = 0;
    for (int i = len - 1; i >= 0; i--) {
        num += (str[i] - '0') * (int)pow(10.0, len - 1 - i);
    }
    return num;
}

double convert_to_double(char str[], int len) {
    str[len] = '\0';
    char *bf_decimal_pt = strtok(str, ".");
    double num = 0.0;
    int len_bf = (int) strlen(bf_decimal_pt);
    for (int i = len_bf - 1; i >= 0; i--) {
        num += (str[i] - '0') * pow(10.0, len_bf - 1 - i);
    }
    char *aft_decimal_pt = bf_decimal_pt + len_bf + 1;
    int len_aft = (int) strlen(aft_decimal_pt);
    for (int i = 0; i <= len_aft - 1; i++) {
        num += (aft_decimal_pt[i] - '0') * pow(10.0, -1 - i);
    }
    return num;
}

Check check_parentheses(int l, int r, Token tokens[]) {
    if (tokens[l].str[0] != '(' || tokens[r].str[0] != ')') {
        return FalseCk;
    } else {
        int count_pth = 1;
        int record = 0;
        for (int i = l + 1; i <= r; i++) {
            if (count_pth < 0) {
                return ErrorCk;
            }
            if (count_pth == 0) {
                record = 1;
            }
            if (tokens[i].str[0] == '(') {
                count_pth++;
            } else if (tokens[i].str[0] == ')') {
                count_pth--;
            }
        }

        if (count_pth == 0) {
            if (record == 1) {
                return FalseCk;
            } else {
                return TrueCk;
            }
        } else {
            return ErrorCk;
        }
    }
}

Check check_minus_operator(int l, int r, Token tokens[]) {
    for (int i = l; i < r; i++) {
        if (tokens[i].type == OPERATOR
            && tokens[i + 1].type == OPERATOR
            && tokens[i + 1].str[0] != '$'
            && tokens[i + 1].str[0] != '-'
            && tokens[i + 1].str[0] != '('
            && tokens[i].str[0] != ')') {
            return ErrorCk;
        }
    }
    int judge = 0;
    if (tokens[l].str[0] == '-') {
        if (tokens[l + 1].str[0] == '('
            || tokens[l + 1].type == INTEGER
            || tokens[l + 1].type == FLOAT
            || tokens[l + 1].type == VARIABLE
            || tokens[l + 1].str[0] == '-'
            || tokens[l + 1].str[0] == '$') {
            judge = 1;
            tokens[l].str[0] = '$';
        }
    } else if (tokens[l].str[0] == '*'
               || tokens[l].str[0] == '/'
               || tokens[l].str[0] == '+') {
        return ErrorCk;
    }
    if (r > l + 1) {
        for (int i = l + 1; i < r; i++) {
            if (tokens[i].str[0] == '-') {
                if (tokens[i - 1].str[0] == '('
                    || tokens[i - 1].str[0] == '+'
                    || tokens[i - 1].str[0] == '-'
                    || tokens[i - 1].str[0] == '*'
                    || tokens[i - 1].str[0] == '/'
                    || tokens[i - 1].str[0] == '$') {
                    tokens[i].str[0] = '$';
                    judge = 1;
                }
            }
        }
        if(tokens[r].type == OPERATOR && tokens[r].str[0] != ')'){
            return ErrorCk;
        }
        if (judge) {
            return TrueCk;
        }
        return FalseCk;
    } else if(r == l + 1){
        if(tokens[r].type == OPERATOR){
            return ErrorCk;
        }
    }
}

Op SrhPrimaryOp(int l, int r, Token tokens[]) {
    int PrimaryOp[1200] = {0};
    int len_of_PrimaryOp = 0;
    for (int i = l; i <= r; i++) {
        if (tokens[i].str[0] == '+' || tokens[i].str[0] == '-') {
            if (len_of_PrimaryOp == 1 && tokens[PrimaryOp[0]].str[0] != '(') {
                PrimaryOp[0] = i;
            } else {
                PrimaryOp[len_of_PrimaryOp] = i;
                len_of_PrimaryOp++;
            }
        } else if (tokens[i].str[0] == '*' || tokens[i].str[0] == '/') {
            if (len_of_PrimaryOp == 1 && (tokens[PrimaryOp[0]].str[0] == '*'
                                          || tokens[PrimaryOp[0]].str[0] == '/')) {
                PrimaryOp[0] = i;
            } else if (len_of_PrimaryOp != 1
                       || (len_of_PrimaryOp == 1 && tokens[PrimaryOp[0]].str[0] == '(')) {
                PrimaryOp[len_of_PrimaryOp] = i;
                len_of_PrimaryOp++;
            }
        } else if (tokens[i].str[0] == '(') {
            PrimaryOp[len_of_PrimaryOp] = i;
            len_of_PrimaryOp++;
        } else if (tokens[i].str[0] == ')') {
            for (int j = len_of_PrimaryOp - 1; j >= 0 ; j--) {
                if (tokens[PrimaryOp[j]].str[0] == '(') {
                    len_of_PrimaryOp = j;
                    break;
                }
            }
        }
    }
    if (len_of_PrimaryOp != 0) {
        Op PrOp = {0, 0};
        PrOp.position = PrimaryOp[0];
        PrOp.type = tokens[PrimaryOp[0]].str[0];
        return PrOp;
    } else {
        if (tokens[l].str[0] == '$') {
            Op PrOp = {0, 0};
            PrOp.position = l;
            PrOp.type = '$';
            return PrOp;
        } else {
            Op Error = {0, 0};
            Error.type = '!';
            return Error;
        }
    }
}

Value meetValue(Value v1, Value v2, Op op) {
    if (v1.type == ERROR_val || v2.type == ERROR_val) {
        Value ReturnError;
        ReturnError.type = ERROR_val;
        return ReturnError;
    }
    if (v1.type != v2.type) {
        if (v1.type == INT_val) {
            v1.val.fVal = (double) v1.val.iVal;
            v1.type = FLOAT_val;
        } else if (v2.type == INT_val) {
            v2.val.fVal = (double) v2.val.iVal;
            v2.type = FLOAT_val;
        }
    }
    Value Return;
    switch (op.type) {
        case '+':
            if (v1.type == INT_val) {
                Return.type = INT_val;
                Return.val.iVal = v1.val.iVal + v2.val.iVal;
            } else {
                Return.type = FLOAT_val;
                Return.val.fVal = v1.val.fVal + v2.val.fVal;
            }
            return Return;
        case '-':
            if (v1.type == INT_val) {
                Return.type = INT_val;
                Return.val.iVal = v1.val.iVal - v2.val.iVal;
            } else {
                Return.type = FLOAT_val;
                Return.val.fVal = v1.val.fVal - v2.val.fVal;
            }
            return Return;
        case '*':
            if (v1.type == INT_val) {
                Return.type = INT_val;
                Return.val.iVal = v1.val.iVal * v2.val.iVal;
            } else {
                Return.type = FLOAT_val;
                Return.val.fVal = v1.val.fVal * v2.val.fVal;
            }
            return Return;
        case '/':
            if (v1.type == INT_val) {
                Return.type = INT_val;
                Return.val.iVal = v1.val.iVal / v2.val.iVal;
            } else {
                Return.type = FLOAT_val;
                Return.val.fVal = v1.val.fVal / v2.val.fVal;
            }
            return Return;
        default:
            assert(0);
    }
}

Value eval(int l, int r, Token tokens[]) {
    if (l > r) {
        Value error;
        error.type = ERROR_val;
        return error;
    } else if (l == r) {
        if (tokens[l].type == INTEGER) {
            Value eval_int;
            eval_int.type = INT_val;
            eval_int.val.iVal = tokens[l].val_of_nums.INT_NUM;
            return eval_int;
        } else if (tokens[l].type == FLOAT) {
            Value eval_double;
            eval_double.type = FLOAT_val;
            eval_double.val.fVal = tokens[l].val_of_nums.FLOAT_NUM;
            return eval_double;
        } else if (tokens[l].type == VARIABLE && tokens[l].isLoaded_int == 1) {
            Value eval_iVar;
            eval_iVar.type = INT_val;
            eval_iVar.val.iVal = tokens[l].val_of_nums.INT_NUM;
            return eval_iVar;
        } else if (tokens[l].type == VARIABLE && tokens[l].isLoaded_double == 1) {
            Value eval_fVar;
            eval_fVar.type = FLOAT_val;
            eval_fVar.val.fVal = tokens[l].val_of_nums.FLOAT_NUM;
            return eval_fVar;
        } else if (tokens[l].type == VARIABLE) {
            Value eval_error;
            eval_error.type = ERROR_val;
            return eval_error;
        } else {
            Value eval_error;
            eval_error.type = ERROR_val;
            return eval_error;
        }
    } else if (check_parentheses(l, r, tokens) == TrueCk) {
        return eval(l + 1, r - 1, tokens);
    } else if (check_parentheses(l, r, tokens) == ErrorCk) {
        Value ReturnError;
        ReturnError.type = ERROR_val;
        return ReturnError;
    } else if (check_minus_operator(l, r, tokens) == ErrorCk) {
        Value ReturnError;
        ReturnError.type = ERROR_val;
        return ReturnError;
    } else {
        Op op = SrhPrimaryOp(l, r, tokens);
        if (op.type == '$') {
            Value val0 = eval(l + 1, r, tokens);
            if (val0.type == INT_val) {
                val0.val.iVal = (-1) * val0.val.iVal;
            } else if (val0.type == FLOAT_val) {
                val0.val.fVal = (-1) * val0.val.fVal;
            }
            return val0;
        } else if (op.type == '!') {
            Value Error;
            Error.type = ERROR_val;
            return Error;
        }
        Value val1 = eval(l, op.position - 1, tokens);
        Value val2 = eval(op.position + 1, r, tokens);
        return meetValue(val1, val2, op);
    }
}

void load(Token var, Value val) {
    if (val.type == INT_val) {
        variables[var.position].isLoaded = 1;
        variables[var.position].value.i_val = val.val.iVal;
        variables[var.position].type = INT;
    } else if (val.type == FLOAT_val) {
        variables[var.position].isLoaded = 1;
        variables[var.position].value.f_val = val.val.fVal;
        variables[var.position].type = DOUBLE;
    }
}

Value evalAssign(int l, int r, Token tokens[]) {
    int isAssign = 0;
    int RCD = 0;
    if(l > r){
        Value ErrorReturn;
        ErrorReturn.type = ERROR_val;
        return ErrorReturn;
    }
    for (int i = l; i <= r; i++) {
        if (tokens[i].str[0] == '=') {
            isAssign = 1;
            RCD = i;
            break;
        }
    }
    if (isAssign) {
        //process the assignment sentence
        if (l == r) {
            Value ErrorReturn;
            ErrorReturn.type = ERROR_val;
            return ErrorReturn;
        }
        if (check_parentheses(l, r, tokens) == TrueCk) {
            return evalAssign(l + 1, r - 1, tokens);
        } else if (check_parentheses(l, r, tokens) == ErrorCk) {
            Value ErrorReturn;
            ErrorReturn.type = ERROR_val;
            return ErrorReturn;
        } else if (RCD != l + 1 || tokens[l].type != VARIABLE) {
            Value ErrorReturn;
            ErrorReturn.type = ERROR_val;
            return ErrorReturn;
        } else {
            Value val = evalAssign(RCD + 1, r, tokens);
            load(tokens[l], val);
            return val;
        }
    } else {
        return eval(l, r, tokens);
    }
}

void printValue(Value v) {
    switch (v.type) {
        case INT_val:
            printf("%d\n", v.val.iVal);
            break;
        case FLOAT_val:
            printf("%.6f\n", v.val.fVal);
            break;
        case ERROR_val:
            printf("Error\n");
            break;
        default:
            assert(0);
    }
}