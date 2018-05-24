/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "lottery.h"

static char* file_Name;
static char c;
static int* drawed;
static bool drew = false;

bool init_lottery(char* filename, char sep){
    FILE* fd= fopen(filename, "r");
    c = sep;
    drew = false;
    file_Name = filename;
    if(fd == NULL)return false;
    fclose(fd);
    return true;
}
bool get_tip(int tip, int* array){
    FILE* fd= fopen(file_Name, "r");
    char input[MAX_LINE_LEN] = {0};
    int data = 0;
    if(tip < 0 || fd == 0){
        fclose(fd);
        return false;
    }
    char* output = fgets(input, MAX_LINE_LEN, fd);
    while(output != NULL && data < tip) {
        output = fgets(input, MAX_LINE_LEN, fd);
        data++;
        if (output != input) {
            fclose(fd);
            return false;
        }
    }
    int pos = 0;
    while(input[pos] !=c&& pos < UUID_LEN){
        pos++;
    }

    int insertionpos = 0;
    int f = 0;
    while(insertionpos < 6){
        pos++;
        if(input[pos]<= '9' && input[pos]>= '0'){
            f = f*10+ (input[pos] - '0');
        }
        else{
            array[insertionpos] = f;
            f = 0;
            insertionpos++;
        }
    }
    fclose(fd);
    return true;
}
bool set_drawing(int* array){
    drew = true;
    drawed = array;
    return false;
}
int get_tip_result(int tip){
    if(!drew ) return -1;
    int x[6];
    if(!get_tip(tip, x)) return -2;
    int count = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if(x[i] == drawed[j]) count++;
        }
    }
    return count;
}
int get_right_tips_count(int tip){
    if(!drew|| tip < 0 || tip > TIP_SIZE) return -1;
    int y = 0;
    int count = 0;
    int x = 0;
    while(x != -2&& x != -1){
        x = get_tip_result(y);
        if(x == tip)count++;
        y++;
    }
    return count;
}
