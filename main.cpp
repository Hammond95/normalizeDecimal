#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>

using namespace std;

char* normalizeDecimal(char *);
int evaluatePrecision(char *);
void remove_all_chars(char* , char);

int main()
{   printf("%s\n",normalizeDecimal("0.7972"));
    printf("%s\n",normalizeDecimal("-0.8232"));
    printf("%s\n",normalizeDecimal("9.6179"));
    printf("%s\n",normalizeDecimal("-0.1999"));
    printf("%s\n",normalizeDecimal("5.551115E-17"));
    printf("%s\n",normalizeDecimal("-1.11022E-16"));
    printf("%s\n",normalizeDecimal("-2.77556E-17"));
    printf("%s\n",normalizeDecimal("1.387779E-17"));
    printf("%s\n",normalizeDecimal("-3.46945E-18"));
    printf("%s\n",normalizeDecimal("1.734723E-18"));
    printf("%s\n",normalizeDecimal("1.387779E-17"));
    printf("%s\n",normalizeDecimal("11111.387779E-17"));
    printf("%s\n",normalizeDecimal("100000000000.33333")); //Gives --> 100000000000.33332824707031250
    printf("%s\n",normalizeDecimal("123ABCE11")); //Gives --> 123

    return 0;
}

/* ********************************************
 * Converts any type of decimal value (both in
 * normal or scientific form) to the normal
 * form.
 * ********************************************/
char* normalizeDecimal(char *s)
{
    double decval;
    char * localstrcp = NULL;
    string temp;
    int precision = 0;
    int i;
    char static teststr [100];

    precision=evaluatePrecision(s);
    if(precision==0)
        return s;

    istringstream os(s);
    os >> decval;
    std::ostringstream ss;
    ss.precision(precision);
    ss << std::fixed << decval;
    temp = ss.str();

    localstrcp = new char[temp.length()*sizeof(char)+1];
    if(localstrcp==NULL){
        delete[] localstrcp;
        return s;
    }

    sprintf(localstrcp, "%s", temp.c_str());

    for(i=0; i<(int signed)strlen(localstrcp); i++){
        teststr[i] = localstrcp[i];
    } teststr[i] = '\0';

    delete[] localstrcp;

    return teststr;
}

/* ********************************************
 * Given a string decimal number both in
 * normal or scientific form, evaluates
 * the number of digits of precision needed
 * to convert correctly that number.
 * ********************************************/
int evaluatePrecision(char * s)
{
    char *sCopy = NULL;
    char *mantissa = NULL;
    char *tok = NULL;
    int precision = 0;
    int exp = 0;

    sCopy = new char[strlen(s)*sizeof(char)+1];
    if(sCopy==NULL){
        delete[] sCopy;
        return 0;
    }
    strcpy(sCopy,s);

    /*Convert to upper case*/
    char *w = sCopy;
    while (*w)
    {   *w = toupper((unsigned char) *w);
        w++;
    }

    tok = strtok(sCopy,"E");
    /*Not in scientific notation*/
	if(tok==NULL)
	{	precision = strlen(sCopy);
	    delete[] sCopy;
		return precision;
	}
	/*Is in scientific notation*/
	else
	{   mantissa = new char[strlen(tok)*sizeof(char)+1];
	    if(mantissa==NULL){
            delete[] mantissa;
            delete[] sCopy;
            return 0;
	    }
	    strcpy(mantissa,tok);
        remove_all_chars(mantissa,'.');
        precision += strlen(mantissa);

		tok = strtok (NULL, "E");
		if(tok==NULL)
        {   delete[] mantissa;
            delete[] sCopy;
            return precision;
		}
		else
		{   exp = atoi(tok);
            if(exp!=0)
                precision += abs(exp);
		}
	}
	delete[] mantissa;
    delete[] sCopy;

    return precision;
}

/* ********************************************
 * Remove all occurrences of a character from
 * a string.
 * ********************************************/
void remove_all_chars(char* str, char c)
{
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}
