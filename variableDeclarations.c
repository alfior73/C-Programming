/* GLOBAL, AUTO, and STATIC VARIABLE DECLARATION EXAMPLE */

    #include <stdio.h>

    int globalvar = 2;  /* global variable initialized only once */
                        /* and its value is always held in memory*/

    /*************************************************************
    **
    ** Function - printit
    **
    ** Description - Just increments and prints a set of local,
    **               static, and global variables
    **
    ** Parameters:  none
    **
    ** Returns:  void
    **
    **************************************************************/ 

    void printit()
    {   
        static int staticvar = 2; /* static initialized only once */
                                  /* value is always held in memory */

        int autovar = 2; /* local variable within printit */

        globalvar++;
        staticvar++;
        autovar++;

        /* Time line 2 */

        printf("globalvar = %d \n",   globalvar);
        printf("staticvar = %d \n",   staticvar);
        printf("autovar   = %d \n\n", autovar); 

    } /* printit */

    int main()
    {

        int x;    /* local variable within main */    

        /* Time line 1 */

        /* Call printit function three times */
        printit();
        printit();
        printit();

        x = 5;

        /* Time line 3 */
        return(0);

    } /* main */
