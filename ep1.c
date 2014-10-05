#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <float.h>
#include <time.h>

#define nmax 700

#define FAIL 0
#define SUCCESS 1

void printf_matrix(int n, double A[][nmax])
{
  int i, j;
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
	{
	  printf ("%lf", A[i][j]);
	  if (j != n - 1)
	    printf ("\t");
	}
      if (i != n - 1)
	printf ("\n");
    }
}

/*
 *    forward_substitution
 *
 **Descrição:
 * Resolve um sistema triangular inferior
 * da forma
 *            Ax = b.
 * De forma orientado a linhas.
 *
 **Argumentos:
 * n é a dimensão da matriz A;
 * A é uma matriz triangular inferior;
 * b é um vetor.
 *
 **Resposta:
 * Quando A for singular:
 *    retorna -1;
 * Quando A for não singular:
 *    retorna 0;
 *    x é armazenado em b.
 */
int forward_substitution (int n, double A[][nmax], double b[])
{
  int i, j;
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < i; j++)
	b[i] -= A[i][j] * b[j];
      if (!A[i][i])
      	return -1;
      b[i] /= A[i][i];
    }
  return 0;
}

/*
 *    column_oriented_forward_substitution
 *
 **Descrição:
 * Resolve um sistema triangular inferior
 * da forma
 *            Ax = b.
 * De forma orientado a colunas.
 *
 **Argumentos:
 * n é a dimensão da matriz A;
 * A é uma matriz triangular inferior;
 * b é um vetor.
 *
 **Resposta:
 * Quando A for singular:
 *    retorna -1;
 * Quando A for não singular:
 *    retorna 0;
 *    x é armazenado em b.
 */
int column_oriented_forward_substitution (int n, double A[][nmax], double b[])
{
  int i, j;
  for (j = 0; j < n; j++)
    {
      if (!A[j][j])
      	return -1;
      b[j] /= A[j][j];
      for (i = j + 1; i < n; i++)
	b[i] -= A[i][j] * b[j];
    }
  return 0;
}

/*
 *    forward_substitution_modified
 *
 **Descrição:
 * Resolve um sistema triangular inferior
 * da forma
 *            Ly = b.
 * De forma orientado a linhas.
 *
 **Argumentos:
 * n é a dimensão da matriz L;
 * L é uma matriz triangular inferior
 * com todos os elementos da diagonal 1;
 * b é um vetor.
 *
 **Resposta:
 * y é armazenado em b
 */
void forward_substitution_modified (int n, double L[][nmax], double b[])
{
  int i, j;
  for (i = 0; i < n; i++)
      for (j = 0; j < i; j++)
	b[i] -= L[i][j] * b[j];
}

/*
 *    column_oriented_forward_substitution_modified
 *
 **Descrição:
 * Resolve um sistema triangular inferior
 * da forma
 *            Ly = b.
 * De forma orientado a colunas.
 *
 **Argumentos:
 * n é a dimensão da matriz L;
 * L é uma matriz triangular inferior
 * com todos os elementos da diagonal 1;
 * b é um vetor.
 *
 **Resposta:
 * y é armazenado em b
 */
void column_oriented_forward_substitution_modified (int n, double L[][nmax], double b[])
{
  int i, j;
  for (j = 0; j < n; j++)
    for (i = j + 1; i < n; i++)
      b[i] -= L[i][j] * b[j];
}

/*
 *    back_substitution
 *
 **Descrição:
 * Resolve um sistema triangular superior
 * da forma
 *            Ux = y.
 * De forma orientado a linhas.
 *
 **Argumentos:
 * n é a dimensão da matriz U;
 * U é uma matriz triangular superior;
 * y é um vetor.
 *
 **Resposta:
 * Quando U é singular:
 *    retorna -1;
 * Quando U é não singular:
 *    retorna 0;
 *    x é armazenado em y.
 */
int back_substitution (int n, double U[][nmax], double y[])
{
  int i, j;
  for (i = n - 1; i >= 0; i--)
    {
      for (j = i + 1; j < n; j++)
	y[i] -= U[i][j] * y[j];
      if (!U[i][i])
	return -1;
      y[i] /= U[i][i];
    }
  return 0;
}


/*
 *    column_oriented_back_substitution
 *
 **Descrição:
 * Resolve um sistema triangular superior
 * da forma
 *            Ux = y.
 * De forma orientado a colunas.
 *
 **Argumentos:
 * n é a dimenção da matriz U.
 * U é uma matriz triangular superior.
 * y é um vetor.
 *
 **Resposta:
 * Quando U é singular:
 *    retorna -1;
 * Quando U é não singular:
 *    retorna 0;
 *    x é armazenado em y.
 */
int column_oriented_back_substitution (int n, double U[][nmax], double y[])
{
  int i, j;
  for (j = n - 1; j >= 0; j--)
    {
      if (!U[j][j])
	return -1;
      y[j] /= U[j][j];
      for (i = j - 1; i >= 0; i--)
	y[i] -= U[i][j] * y[j];
    }
  return 0;
}

/*
 *    lurow_without_pivoting
 *
 **Descrição:
 * Faz a decomposição LU de uma matriz A.
 * Orientado á linhas.
 *
 **Argumentos:
 * n é a dimensão da A;
 * A é uma matriz qualquer;
 *
 **Resposta:
 * Quando existir uma ou mais matrizes principais de A singulares:
 *    retorna -1;
 * Quando todas as matrizes principais de A forem não singulares:
 *    retorna 0;
 *    L é armazenado sem a diagonal com 1's
 *     na parte triangular inferior de A;
 *    U é armazenado na parte triangular superior de A;
 */
int lurow_without_pivoting (int n, double A[][nmax])
{
  int i, j, k;
  for (i = 1; i < n; i++)
    {
      /* Calcula L */
      for (j = 0; j < i; j++)
	{
	  for (k = 0; k < j; k++)
	    A[i][j] -= A[i][k] * A[k][j];
	  A[i][j] /= A[j][j];
	}

      /* Calcula o U */
      for (j = i; j < n; j++)
	for (k = 0; k < i; k++)
	  A[i][j] -= A[i][k] * A[k][j];

      /* 
       * Verifica se o elemento da diagonal
       * na matriz A é zero.
       */
      if (fabs(A[i][i]) <= DBL_EPSILON)
	return -1;
    }
  return 0;
}

/*
 *    swap
 *
 **Descrição:
 * Faz a troca de valores de duas variáveis do tipo double.
 *
 **Argumentos:
 * *a e *b são ponteiros para variáveis do tipo double.
 */
void swap(double *a, double *b)
{
  double mem;
  mem = *a;
  *a = *b;
  *b = mem;
}


/*
 *    pivoting
 *
 **Descrição:
 * Faz o pivoteamento da k-ésima iteração da eliminação gausiana.
 *
 **Argumentos:
 * n é a dimensão da A;
 * A é uma matriz qualquer;
 * k número de iterações;
 * p vetor que guarda a informação da troca de linha.
 *
 **Resposta:
 * A recebe a matriz A pivoteada;
 * p quarda a linha trocada.
 */
void pivoting (int n, double A[][nmax], int k, int p[])
{
  int i, j;
  double a = fabs (A[k][k]);
  p[k] = k;
  for (i = k + 1; i < n; i++)
    if (a < fabs (A[i][k])){
      a = fabs (A[i][k]);
      p[k] = i;
    }
  if (p[k] != k)
    for (j = 0; j < n; j++)
      swap(&A[k][j], &A[p[k]][j]);
}

 
/*
 *    lurow
 *
 **Descrição:
 * Faz a decomposição LU de uma matriz A com pivoteamento.
 * Orientado a linhas.
 *
 **Argumentos:
 * n é a dimensão da A;
 * A é uma matriz qualquer;
 * p é um vetor de permutações de linhas.
 *
 **Resposta:
 * Quando a matriz A for singular:
 *    retorna -1;
 * Quando a matriz A for não singular:
 *    retorna 0;
 *    L é armazenado sem a diagonal com 1's
 *     na parte triangular inferior de A;
 *    U é armazenado na parte triangular superior de A;
 */
int lurow (int n, double A[][nmax], int p[])
{
  int i, j, k;
  for (i = 0; i < n; i++)
    {
      pivoting(n, A, i, p);

      /* Calcula L */
      for (j = 0; j < i; j++)
	{
	  for (k = 0; k < j; k++)
	    A[i][j] -= A[i][k] * A[k][j];
	  A[i][j] /= A[j][j];
	}

      /* Calcula U */
      for (j = i; j < n; j++)
	for (k = 0; k < i; k++)
	  A[i][j] -= A[i][k] * A[k][j];

      /* 
       * Verifica se o elemento da diagonal
       * na matriz A é zero.
       */
      if (fabs(A[i][i]) <= DBL_EPSILON)
	    return -1;
    }
  return 0;
}

/*
 *    lucol_without_pivoting
 *
 **Descrição:
 * Faz a decomposição LU de uma matriz A sem pivoteamento.
 * Orientado a colunas.
 *
 **Argumentos:
 * n é a dimensão da A;
 * A é uma matriz qualquer;
 *
 **Resposta:
 * Quando existir uma ou mais matrizes principais de A singulares:
 *    retorna -1;
 * Quando todas as matrizes principais de A forem não singulares:
 *    retorna 0;
 *    L é armazenado sem a diagonal com 1's
 *     na parte triangular inferior de A;
 *    U é armazenado na parte triangular superior de A;
 */
int lucol_without_pivoting (int n, double A[][nmax])
{
  int i, j, k;
  for (j = 0; j < n; j++)
    {
      /* Calcula o U */
      for (i = 0; i <= j; i++)
	for (k = 0; k < i; k++)
	  A[i][j] -= A[i][k] * A[k][j];

      /*
       * Verifica se o elemento da diagonal
       * na matriz A é zero.
       */
      if (fabs(A[j][j]) <= DBL_EPSILON)
	return -1;

      /* Calcula o L */
      for (i = j + 1; i < n; i++)
	{
	  for (k = 0; k < j; k++)
	    A[i][j] -= A[i][k] * A[k][j];
	  A[i][j] /= A[j][j];
	}
    }
  return 0;
}

/*
 *    lucol
 *
 **Descrição:
 * Faz a decomposição LU de uma matriz A com pivoteamento.
 * Orientado a colunas.
 *
 **Argumentos:
 * n é a dimensão da A;
 * A é uma matriz qualquer;
 *
 **Resposta:
 * Quando a matriz A for singular:
 *    retorna -1;
 * Quando a matriz A for não singular:
 *    retorna 0;
 *    L é armazenado sem a diagonal com 1's
 *     na parte triangular inferior de A;
 *    U é armazenado na parte triangular superior de A;
 */
int lucol (int n, double A[][nmax], int p[])
{
  int i, j, k;
  for (j = 0; j < n; j++)
    {
      pivoting (n, A, j, p);

      /* Calcula o U */
      for (i = 0; i <= j; i++)
	for (k = 0; k < i; k++)
	  A[i][j] -= A[i][k] * A[k][j];

      /*
       * Verifica se o elemento da diagonal
       * na matriz A é zero.
       */
      if (fabs(A[j][j]) <= DBL_EPSILON)
	return -1;

      /* Calcula o L */
      for (i = j + 1; i < n; i++)
	{
	  for (k = 0; k < j; k++)
	    A[i][j] -= A[i][k] * A[k][j];
	  A[i][j] /= A[j][j];
	}
    }
  return 0;
}


/*
 *    ssrow
 *
 **Descrição:
 * Soluciona o sistema linear da forma
 *                 LUx=Pb
 * onde LU é a matriz mista, e P é o vetor de permutações.
 * Orientado a linhas.
 *
 **Argumentos:
 * n é a dimensão da LU;
 * LU matriz saída da função lurow.
 *
 **Resposta:
 * Quando não houver solução:
 *    retorna -1;
 * Quando quando houver solução:
 *    retorna 0;
 *    b recebe a solução.
 */
int ssrow (int n, double A[][nmax], int p[], double b[])
{
  int i;
  /*
   * Trocando elementos do vetor b
   * de acordo com o vetor p.
   */
  for (i = 0; i < n; i++)
    if(p[i] != i)
      swap(&b[i], &b[p[i]]);

  /* Encontrando o vetor y */
  forward_substitution_modified (n, A, b);

  /* Encontrando a solução */
  if(!back_substitution (n, A, b))
    return -1;

  return 0;
}

/*
 *    sscol
 *
 **Descrição:
 * Soluciona o sistema linear da forma
 *                 LUx=Pb
 * onde LU é a matriz mista, e P é o vetor de permutações.
 * Orientado a colunas.
 *
 **Argumentos:
 * n é a dimensão da LU;
 * LU matriz saída da função lucol.
 *
 **Resposta:
 * Quando não houver solução:
 *    retorna -1;
 * Quando quando houver solução:
 *    retorna 0;
 *    b recebe a solução.
 */
int sscol (int n, double A[][nmax], int p[], double b[])
{
  int i;
  /*
   * Trocando elementos do vetor b
   * de acordo com o vetor p.
   */
  for (i = 0; i < n; i++)
    if(p[i] != i)
      swap(&b[i], &b[p[i]]);

  /* Encontrando o vetor y */
  column_oriented_forward_substitution_modified (n, A, b);

  /* Encontrando a solução */
  if(column_oriented_back_substitution (n, A, b) != -1)
    return -1;

  return 0;
}

int get_matrix(char *file_name, int *n, double A[][nmax], double b[]){
  FILE *pFile;
  int i, j, k;
  double x;
  if(!(pFile = fopen (file_name, "r")))
    {
      perror ("Falha ao abrir o arquivo");
      return -1;
    }

  if(fscanf (pFile, "%d", n) == EOF)
    return -1;

  for (k = 0; k < *n * *n; k++){
    fscanf (pFile, "%d %d %lf", &i, &j, &x);
    A[i][j] = x;
  }

  for (k = 0; k < *n; k++){
    fscanf (pFile, "%d %lf\n", &i, &x);
    b[i] = x;
  }
  fclose(pFile);
  return 0;
}

int test1 ()
{
  int n = 3, i;
  double A[nmax][nmax] =
    {
      {5, 0, 0},
      {2, -4, 0},
      {1, 2, 3}
    }, b[3] = {15, -2, 10}, b_esperado[3] = {3, 2, 1};
  if(!forward_substitution (n, A, b))
    {
      for (i = 0; i < n; i++)
	if (fabs(b[i] - b_esperado[i]) >= FLT_EPSILON)
	  return FAIL;
    }
  else
    return FAIL;
  return SUCCESS;
}

int test2 ()
{
  int n = 3, i;
  double A[nmax][nmax] =
    {
      {5, 0, 0},
      {2, -4, 0},
      {1, 2, 3}
    }, b[3] = {15, -2, 10}, b_esperado[3] = {3, 2, 1};
  if(!column_oriented_forward_substitution (n, A, b))
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
  int n = 3;
  double A[nmax][nmax] =
    {
      {0, 0, 0},
      {2, -4, 0},
      {1, 2, 3}
    }, b[3] = {15, -2, 10};
  if(!forward_substitution (n, A, b))
    return FAIL;
  else
    return SUCCESS;
}

int test4 ()
{
  int n = 3;
  double A[nmax][nmax] =
    {
      {0, 0, 0},
      {2, -4, 0},
      {1, 2, 3}
    }, b[3] = {15, -2, 10};
  if(!column_oriented_forward_substitution (n, A, b))
    return FAIL;
  else
    return SUCCESS;
}

int test5 ()
{
  int n = 4, i;
  double A[nmax][nmax] = 
    {
      {3, 2,  1, 0},
      {0, 1,  2, 3},
      {0, 0, -2, 1},
      {0, 0,  0, 4}
    }, b[4] = {-10, 10, 1, 12}, b_esperado[4] = {-3, -1, 1, 3};
  if(!back_substitution (n, A, b))
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
  double A[nmax][nmax] = 
    {
      {3, 2,  1, 0},
      {0, 1,  2, 3},
      {0, 0, -2, 1},
      {0, 0,  0, 4}
    }, b[4] = {-10, 10, 1, 12}, b_esperado[4] = {-3, -1, 1, 3};
  if(!column_oriented_back_substitution (n, A, b))
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
  int n = 4;
  double A[nmax][nmax] = {
    {0, 2,  1, 0},
    {0, 1,  2, 3},
    {0, 0, -2, 1},
    {0, 0,  0, 4}
  }, b[4] = {-10, 10, 1, 12};
  if(!back_substitution (n, A, b))
    return FAIL;
  else
    return SUCCESS;
}

int test8 ()
{
  int n = 4;
  double A[nmax][nmax] = 
    {
      {0, 2,  1, 0},
      {0, 1,  2, 3},
      {0, 0, -2, 1},
      {0, 0,  0, 4}
    }, b[4] = {-10, 10, 1, 12};
  if(!column_oriented_back_substitution (n, A, b))
    return FAIL;
  else
    return SUCCESS;
}

int test9 ()
{
  int n = 4, i, j;
  double A[nmax][nmax] =
    {
      { 2,  4,  2,  3},
      {-2, -5, -3, -2},
      { 4,  7,  6,  8},
      { 6, 10,  1, 12}
    };
  double A_expected[nmax][nmax] =
    {
      { 2,  4,  2, 3},
      {-1, -1, -1, 1},
      { 2,  1,  3, 1},
      { 3,  2, -1, 2}
    };
  lurow_without_pivoting (n, A);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if(A[i][j] != A_expected[i][j])
	return FAIL;
  return SUCCESS;
}

int test10 ()
{
  int n = 4;
  double A[nmax][nmax] =
    {
      {2,  4, 2,  3},
      {2,  4, 2,  3},
      {4,  7, 6,  8},
      {6, 10, 1, 12}
    };
  if(lurow_without_pivoting (n, A) != -1)
    return FAIL;
  return SUCCESS;
}

int test11 ()
{
  int n = 4, i, j, p[4], p_expected[4] = {0, 1, 2, 3};
  double A[nmax][nmax] =
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    };
  double A_expected[nmax][nmax] =
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    };
  lurow (n, A, p);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (A[i][j] != A_expected[i][j])
	return FAIL;
  for (i = 0; i < n; i++)
    if (p[i] != p_expected[i])
      return FAIL;
  return SUCCESS;
}

int test12 ()
{
  int n = 4, i, j, p[4], p_expected[4] = {0, 2, 2, 3};
  double A[nmax][nmax] =
    {
      {1, 0, 0, 0},
      {0, 0, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 1}
    };
  double A_expected[nmax][nmax] =
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    };
  lurow (n, A, p);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (A[i][j] != A_expected[i][j])
	return FAIL;
  for (i = 0; i < n; i++)
    if (p[i] != p_expected[i])
      return FAIL;
  return SUCCESS;
}

int test13 ()
{
  int n = 4, i, j;
  double A[nmax][nmax] =
    {
      { 2,  4,  2,  3},
      {-2, -5, -3, -2},
      { 4,  7,  6,  8},
      { 6, 10,  1, 12}
    };
  double A_expected[nmax][nmax] =
    {
      { 2,  4,  2, 3},
      {-1, -1, -1, 1},
      { 2,  1,  3, 1},
      { 3,  2, -1, 2}
    };
  lucol_without_pivoting (n, A);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if(A[i][j] != A_expected[i][j])
	return FAIL;
  return SUCCESS;
}

int test14 ()
{
  int n = 4;
  double A[nmax][nmax] =
    {
      {2,  4, 2,  3},
      {4,  7, 6,  8},
      {2,  4, 2,  3},
      {6, 10, 1, 12}
    };
  if(lucol_without_pivoting (n, A) != -1)
    return FAIL;
  return SUCCESS;
}

int test15 ()
{
  int n = 4, i, j, p[4], p_expected[4] = {0, 2, 2, 3};
  double A[nmax][nmax] =
    {
      {1, 0, 0, 0},
      {0, 0, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 1}
    };
  double A_expected[nmax][nmax] =
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    };
  lucol (n, A, p);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (A[i][j] != A_expected[i][j])
	return FAIL;
  for (i = 0; i < n; i++)
    if (p[i] != p_expected[i])
      return FAIL;
  return SUCCESS;
}

int test16 ()
{
  int n = 3, i, p[3];
  double A[nmax][nmax] =
    {
      {1, 2, 3},
      {2, 3, 4},
      {3, 4, 1}
    };
  double b[4] = {4, 1, 2};
  double b_expected[4] = {-11.0, 9.0, -1.0};
  lurow (n, A, p);
  ssrow (n, A, p, b);
  for (i = 0; i < n; i++)
    if (fabs(b[i] - b_expected[i]) >= FLT_EPSILON)
      return FAIL;
  return SUCCESS;
}

int test17 ()
{
  int n = 3, i, p[3];
  double A[nmax][nmax] =
    {
      {1, 2, 3},
      {2, 3, 4},
      {3, 4, 1}
    };
  double b[4] = {4, 1, 2};
  double b_expected[4] = {-11.0, 9.0, -1.0};
  lucol (n, A, p);
  sscol (n, A, p, b);
  for (i = 0; i < n; i++)
    if (fabs(b[i] - b_expected[i]) >= FLT_EPSILON)
      return FAIL;
  return SUCCESS;
}

int test18 ()
{
  int n, i;
  int p[nmax];
  double A[nmax][nmax], b[nmax];
  if(get_matrix ("a7.dat", &n, A, b) != 0)
    return FAIL;
  lucol (n, A, p);
  sscol (n, A, p, b);
  for (i = 0; i < n; i++)
    if (fabs((1 + i % (n / 100)) - b[i]) >= FLT_EPSILON)
      return FAIL;
  return SUCCESS;
}

void time_test1 ()
{
  clock_t t;
  int n, p[nmax];
  double A[nmax][nmax], b[nmax];
  get_matrix ("a7.dat", &n, A, b);
  t = -clock();
  lucol (n, A, p);
  sscol (n, A, p, b);
  t += clock();
  printf ("It took me %d clicks (%f seconds).\n",(int)t,((float)t)/CLOCKS_PER_SEC);
}

void time_test2 ()
{
  clock_t t;
  int n, p[nmax];
  double A[nmax][nmax], b[nmax];
  get_matrix ("a7.dat", &n, A, b);
  t = -clock();
  lurow (n, A, p);
  ssrow (n, A, p, b);
  t += clock();
  printf ("It took me %d clicks (%f seconds).\n",(int)t,((float)t)/CLOCKS_PER_SEC);
}

int main ()
{
  int (*test[18]) () =
    {
      test1,
      test2,
      test3,
      test4,
      test5,
      test6,
      test7,
      test8,
      test9,
      test10,
      test11,
      test12,
      test13,
      test14,
      test15,
      test16,
      test17,
      test18
    }, i;
  for (i = 0; i < 18; i++)
    if(test[i] ())
    printf(".");
  else
    printf("F");
  printf("\n");

  time_test1();
  time_test2();
  return 0;
}

