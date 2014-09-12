#include <stdio.h>

/*
 * Considere o sistema
 *                         Gy = b,
 * onde G é não singular, matriz triangular inferior.
 * A função forward_substitution, recebe a dimenção n de G,
 * a própria G e b como parâmetros.
 * Transforma b na solução do sistema y,
 * retornando 0 se G é não singular e -1 caso contrário.
 */
int forward_substitution (int n, double G[][n], double b[])
{
  int i, j;
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < i; j++)
	b[i] -= G[i][j] * b[j];
      if (!G[i][i])
	return -1;
      b[i] /= G[i][i];
    }
  return 0;
}

int column_oriented_forward_substitution (int n, double G[][n], double b[])
{
  int i, j;
  for (j = 0; j < n; j++)
    {
      if (!G[j][j])
	return -1;
      b[j] /= G[j][j];
      for (i = j + 1; i < n; i++)
	b[i] -= G[i][j] * b[j];
    }
  return 0;
}

int back_substitution (int n, double G[][n], double b[])
{
  int i, j;
  for (i = n - 1; i >= 0; i--)
    {
      for (j = i + 1; j < n; j++)
	b[i] -= G[i][j] * b[j];
      if (!G[i][i])
	return -1;
      b[i] /= G[i][i];
    }
  return 0;
}

int column_oriented_back_substitution (int n, double G[][n], double b[])
{
  int i, j;
  for (j = n - 1; j >= 0; j--)
    {
      if (!G[j][j])
	return -1;
      b[j] /= G[j][j];
      for (i = j - 1; i >= 0; i--)
	b[i] -= G[i][j] * b[j];
    }
  return 0;
}

int test1 ()
{
  int n = 3, i;
  double G[3][3] =
    {
      {5, 0, 0},
      {2, -4, 0},
      {1, 2, 3}
    }, b[3] = {15, -2, 10}, b_esperado[3] = {3, 2, 1};
  if(!forward_substitution (n, G, b))
    {
      for (i = 0; i < n; i++)
	if (b_esperado[i] != b[i])
	  return 0;
    }
  else
    return 0;
  return 1;
}

int test2 ()
{
  int n = 3, i;
  double G[3][3] =
    {
      {5, 0, 0},
      {2, -4, 0},
      {1, 2, 3}
    }, b[3] = {15, -2, 10}, b_esperado[3] = {3, 2, 1};
  if(!column_oriented_forward_substitution (n, G, b))
    {
      for (i = 0; i < n; i++)
	if (b_esperado[i] != b[i])
	  return 0;
    }
  else
    return 0;
  return 1;
}

int test3 ()
{
  int n = 3, i;
  double G[3][3] =
    {
      {0, 0, 0},
      {2, -4, 0},
      {1, 2, 3}
    }, b[3] = {15, -2, 10};
  if(!forward_substitution (n, G, b))
    return 0;
  else
    return 1;
}

int test4 ()
{
  int n = 3, i;
  double G[3][3] =
    {
      {0, 0, 0},
      {2, -4, 0},
      {1, 2, 3}
    }, b[3] = {15, -2, 10};
  if(!column_oriented_forward_substitution (n, G, b))
    return 0;
  else
    return 1;
}

int test5 ()
{
  int n = 4, i;
  double G[4][4] = 
    {
      {3, 2,  1, 0},
      {0, 1,  2, 3},
      {0, 0, -2, 1},
      {0, 0,  0, 4}
    }, b[4] = {-10, 10, 1, 12}, b_esperado[4] = {-3, -1, 1, 3};
  if(!back_substitution (n, G, b))
    {
      for (i = 0; i < n; i++)
	if (b_esperado[i] != b[i])
	  return 0;
    }
  else
    return 0;
  return 1;
}

int test6 ()
{
  int n = 4, i;
  double G[4][4] = 
    {
      {3, 2,  1, 0},
      {0, 1,  2, 3},
      {0, 0, -2, 1},
      {0, 0,  0, 4}
    }, b[4] = {-10, 10, 1, 12}, b_esperado[4] = {-3, -1, 1, 3};
  if(!column_oriented_back_substitution (n, G, b))
    {
      for (i = 0; i < n; i++)
	if (b_esperado[i] != b[i])
	  return 0;
    }
  else
    return 0;
  return 1;
}

int test7 ()
{
  int n = 4, i;
  double G[4][4] = {
    {0, 2,  1, 0},
    {0, 1,  2, 3},
    {0, 0, -2, 1},
    {0, 0,  0, 4}
  }, b[4] = {-10, 10, 1, 12};
  if(!back_substitution (n, G, b))
    return 0;
  else
    return 1;
}

int test8 ()
{
  int n = 4, i;
  double G[4][4] = 
    {
      {0, 2,  1, 0},
      {0, 1,  2, 3},
      {0, 0, -2, 1},
      {0, 0,  0, 4}
    }, b[4] = {-10, 10, 1, 12};
  if(!column_oriented_back_substitution (n, G, b))
    return 0;
  else
    return 1;
}

int main ()
{
  int (*test[8]) () =
    {
      test1,
      test2,
      test3,
      test4,
      test5,
      test6,
      test7,
      test8
    }, i;
  for (i = 0; i < 8; i++)
    if(test[i] ())
    printf(".");
  else
    printf("F");
  printf("\n");
  return 0;
}

