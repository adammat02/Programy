#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
  {
    if (argv[i][0] != '-')
    {
      printf("Niepoprawna opcja\n");
      return 0;
    }
    else
    {
      switch (argv[i][1])
      {
      case 'a':
      {
        printf("Podano opcje a\n");
        break;
      }
      case 'b':
      {
        printf("Podano opcje b\n");
        break;
      }
      case 'c':
      {
        if (++i < argc)
        {
          switch (argv[i][0])
          {
          case '1':
          {
            printf("Wybrano opcje c z 1\n");
            break;
          }
          case '2':
          {
            printf("Wybrano opcje c z 2\n");
            break;
          }
          case '3':
          {
            printf("Wybrano opcje c z 3\n");
            break;
          }

          default:
            printf("Do c podany zly argument\n");
            break;
          }
        }
        break;
      }

      default:
        printf("Zla opcja\n");
        break;
      }
    }
  }
}



