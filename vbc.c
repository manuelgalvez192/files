#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static const char *g_input;
static int g_error = 0; // 0 = sin error, 1 = error detectado

static void error(char c)
{
    g_error = 1;
    if (c == '\0')
        printf("Unexpected end of input\n");
    else
        printf("Unexpected token '%c'\n", c);
}

static int parse_expr();
static int parse_term();
static int parse_factor();

static char peek() { return *g_input; }
static char get() { return *g_input ? *g_input++ : '\0'; }

static int parse_factor()
{
    char c = peek();
    if (isdigit(c))
        return get() - '0';
    if (c == '(')
    {
        get();
        int val = parse_expr();
        if (g_error) return 0;
        if (peek() != ')')
        {
            error(peek());
            return 0;
        }
        get();
        return val;
    }
    error(peek());
    return 0;
}

static int parse_term()
{
    int val = parse_factor();
    while (!g_error && peek() == '*')
    {
        get();
        val *= parse_factor();
    }
    return val;
}

static int parse_expr()
{
    int val = parse_term();
    while (!g_error && peek() == '+')
    {
        get();
        val += parse_term();
    }
    return val;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;

    g_input = av[1];
    int result = parse_expr();

    if (!g_error && peek() != '\0')
        error(peek());

    if (!g_error)
        printf("%d\n", result);

    return g_error ? 1 : 0;
}
