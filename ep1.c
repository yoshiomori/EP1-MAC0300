#include <stdio.h>

#define FAIL 0
#define SUCCESS 1

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

int row_oriented_lu_decomposition (int n, double G[][n])
{
  int i, j, k;
  for (i = 1; i < n; i++)
    {
      for (j = 0; j < i; j++)
	{
	  if (!G[j][j])
	    return -1;
	  for (k = 0; k < j; k++)
	    G[i][j] -= G[i][k] * G[k][j];
	  G[i][j] /= G[j][j];
	}
      for (j = i; j < n; j++)
	for (k = 0; k < i; k++)
	  G[i][j] -= G[i][k] * G[k][j];
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
	  return FAIL;
    }
  else
    return FAIL;
  return SUCCESS;
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
    return FAIL;
  return SUCCESS;
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
    return FAIL;
  else
    return SUCCESS;
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
    return FAIL;
  else
    return SUCCESS;
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
	  return FAIL;
    }
  else
    return FAIL;
  return SUCCESS;
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
	  return FAIL;
    }
  else
    return FAIL;
  return SUCCESS;
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
    return FAIL;
  else
    return SUCCESS;
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
    return FAIL;
  else
    return SUCCESS;
}

int test9 ()
{
  int n = 4, i, j;
  double G[4][4] =
    {
      { 2,  4,  2,  3},
      {-2, -5, -3, -2},
      { 4,  7,  6,  8},
      { 6, 10,  1, 12}
    };
  double G_expected[4][4] =
    {
      { 2,  4,  2, 3},
      {-1, -1, -1, 1},
      { 2,  1,  3, 1},
      { 3,  2, -1, 2}
    };
  printf("\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      {
	printf("%lf ", G[i][j]);
	if (j == n - 1)
	  printf("\n");
      }
  printf("%d\n", row_oriented_lu_decomposition (n, G));
  printf("\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      {
	printf("%lf ", G[i][j]);
	if (j == n - 1)
	  printf("\n");
      }
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if(G[i][j] != G_expected[i][j])
	return FAIL;
  return SUCCESS;
}

int main ()
{
  int (*test[9]) () =
    {
      test1,
      test2,
      test3,
      test4,
      test5,
      test6,
      test7,
      test8,
      test9
    }, i;
  for (i = 0; i < 9; i++)
    if(test[i] ())
    printf(".");
  else
    printf("F");
  printf("\n");
  return 0;
}

