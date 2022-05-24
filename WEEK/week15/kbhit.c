#include <conio.h>
#include <stdio.h>

int main( void )
{
   /* Display message until key is pressed. */
   while( !_kbhit() ) {
      	printf("Hit me!! ");

   }
   /* Use _getch to throw key away. */
   printf( "\nKey struck was '%c'\n", _getch() );
}
