#include <unistd.h>
#include <stdarg.h>

void put_str(char *str, int *len)
{
    int i = 0;
    if(!str)
        str = "(null)";
    while(str[i] != '\0')
    {
        *len += write(1, &str[i], 1);
        i++;
    }
    
}

void put_nbr(long long int number, int *len, int base)
{
    char *hexa = "0123456789abcdef";

    if (number < 0)
    {
        number *= -1;
        *len += write(1, "-", 1);
    }
    if(number >= base)
        put_nbr(number/base, len, base);
    *len += write(1, &hexa[number % base], 1);
}

int ft_printf(const char *format, ...)
{   
    int len = 0;
    int i  = 0;
    
    va_list(args);
    va_start(args, format);
    while(format[i] != '\0')
    {
        if (format[i] == '%' && format[i + 1])
        {
            i++;
            if (format[i] == 's')
                put_str(va_arg(args, char *), &len);
            else if(format[i] == 'd')
                put_nbr((long long int)va_arg(args, int), &len, 10);
            else if(format[i] == 'x')
                put_nbr((long long int)va_arg(args, unsigned int), &len, 16); 
        }
        else
            len += write(1, &format[i], 1);
        i++;  
    }
    va_end(args);
    return(len);
}