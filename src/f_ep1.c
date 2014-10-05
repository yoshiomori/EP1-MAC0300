/* main.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__9 = 9;
static integer c__3 = 3;
static integer c__4 = 4;
static integer c__1000 = 1000;

/* Main program */ int MAIN__(void)
{
    /* System generated locals */
    integer i__1, i__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), f_open(olist *), s_rsle(cilist *), e_rsle(void), 
	    f_clos(cllist *), s_cmp(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static real a[1000000]	/* was [1000][1000] */, b[1000];
    static integer i__, j, k, n;
    static real p[1000];
    static char orientacao[6];
    static real num;
    static integer argc;
    extern /* Subroutine */ int exit_(void);
    static char nome_arquivo__[20];
    extern integer iargc_(void), lucol_(integer *, integer *, real *, real *),
	     sscol_(integer *, integer *, real *, real *, real *), lurow_(
	    integer *, integer *, real *, real *), ssrow_(integer *, integer *
	    , real *, real *, real *);
    extern /* Subroutine */ int getarg_(integer *, char *, ftnlen);

    /* Fortran I/O blocks */
    static cilist io___4 = { 0, 6, 0, 0, 0 };
    static cilist io___5 = { 0, 1, 0, 0, 0 };
    static cilist io___8 = { 0, 1, 0, 0, 0 };
    static cilist io___13 = { 0, 1, 0, 0, 0 };
    static cilist io___16 = { 0, 6, 0, 0, 0 };
    static cilist io___17 = { 0, 6, 0, 0, 0 };
    static cilist io___18 = { 0, 6, 0, 0, 0 };
    static cilist io___19 = { 0, 6, 0, 0, 0 };
    static cilist io___20 = { 0, 6, 0, 0, 0 };




/*     Matriz LU */


    argc = iargc_();
    if (argc > 1) {
	getarg_(&c__1, nome_arquivo__, (ftnlen)20);
	getarg_(&c__2, orientacao, (ftnlen)6);
    } else {
	s_wsle(&io___4);
	do_lio(&c__9, &c__1, "Digite o nome do arquivo e se e orientada a li"
		"nha ou coluna. (Ex: m1.dat linha)", (ftnlen)79);
	e_wsle();
	exit_();
    }

    o__1.oerr = 0;
    o__1.ounit = 1;
    o__1.ofnmlen = 20;
    o__1.ofnm = nome_arquivo__;
    o__1.orl = 0;
    o__1.osta = "old";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);

    s_rsle(&io___5);
    do_lio(&c__3, &c__1, (char *)&n, (ftnlen)sizeof(integer));
    e_rsle();
/* Computing 2nd power */
    i__2 = n;
    i__1 = i__2 * i__2;
    for (k = 1; k <= i__1; ++k) {
	s_rsle(&io___8);
	do_lio(&c__3, &c__1, (char *)&i__, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	do_lio(&c__4, &c__1, (char *)&num, (ftnlen)sizeof(real));
	e_rsle();
	a[i__ + 1 + (j + 1) * 1000 - 1001] = num;
    }

    i__1 = n;
    for (k = 1; k <= i__1; ++k) {
	s_rsle(&io___13);
	do_lio(&c__3, &c__1, (char *)&i__, (ftnlen)sizeof(integer));
	do_lio(&c__4, &c__1, (char *)&num, (ftnlen)sizeof(real));
	e_rsle();
	b[i__] = num;
    }

    cl__1.cerr = 0;
    cl__1.cunit = 1;
    cl__1.csta = 0;
    f_clos(&cl__1);

/* ====================================================== */
/*     OPERACAO POR LINHA */

    if (s_cmp(orientacao, "linha", (ftnlen)6, (ftnlen)5) == 0 && lurow_(&n, &
	    c__1000, a, p) == -1) {
	s_wsle(&io___16);
	do_lio(&c__9, &c__1, "Matriz singular.", (ftnlen)16);
	e_wsle();
	exit_();
    }
    if (s_cmp(orientacao, "linha", (ftnlen)6, (ftnlen)5) == 0 && ssrow_(&n, &
	    c__1000, a, p, b) == -1) {
	s_wsle(&io___17);
	do_lio(&c__9, &c__1, "Matriz singular.", (ftnlen)16);
	e_wsle();
	exit_();
    }
/* ====================================================== */
/*     OPERACAO POR COLUNA */

    if (s_cmp(orientacao, "coluna", (ftnlen)6, (ftnlen)6) == 0 && lucol_(&n, &
	    c__1000, a, p) == -1) {
	s_wsle(&io___18);
	do_lio(&c__9, &c__1, "Matriz singular.", (ftnlen)16);
	e_wsle();
	exit_();
    }
    if (s_cmp(orientacao, "coluna", (ftnlen)6, (ftnlen)6) == 0 && sscol_(&n, &
	    c__1000, a, p, b) == -1) {
	s_wsle(&io___19);
	do_lio(&c__9, &c__1, "Matriz singular.", (ftnlen)16);
	e_wsle();
	exit_();
    }
/* ====================================================== */

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsle(&io___20);
	do_lio(&c__4, &c__1, (char *)&b[i__ - 1], (ftnlen)sizeof(real));
	e_wsle();
    }

    return 0;
} /* MAIN__ */


integer lurow_(integer *n, integer *lda, real *a, real *p)
{
    /* System generated locals */
    integer a_dim1, a_offset, ret_val, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, imax;
    static real swap;


    /* Parameter adjustments */
    --p;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	imax = i__;
	j = i__;
	i__2 = *n;
	for (k = i__ + 1; k <= i__2; ++k) {
	    if (a[k + j * a_dim1] > a[imax + j * a_dim1]) {
		imax = k;
	    }
	}

	if (a[imax + j * a_dim1] == 0.f) {
	    ret_val = -1;
	    return ret_val;
	}

	if (imax != i__) {
	    i__2 = *n;
	    for (j = 1; j <= i__2; ++j) {
		swap = a[i__ + j * a_dim1];
		a[i__ + j * a_dim1] = a[imax + j * a_dim1];
		a[imax + j * a_dim1] = swap;
	    }
	}

	p[i__] = (real) imax;

	i__2 = i__ - 1;
	for (j = 1; j <= i__2; ++j) {
	    if (a[j + j * a_dim1] == 0.f) {
		ret_val = -1;
		return ret_val;
	    }

	    i__3 = j - 1;
	    for (k = 1; k <= i__3; ++k) {
		a[i__ + j * a_dim1] -= a[i__ + k * a_dim1] * a[k + j * a_dim1]
			;
	    }
	    a[i__ + j * a_dim1] /= a[j + j * a_dim1];
	}

	i__2 = *n;
	for (j = i__; j <= i__2; ++j) {
	    i__3 = i__ - 1;
	    for (k = 1; k <= i__3; ++k) {
		a[i__ + j * a_dim1] -= a[i__ + k * a_dim1] * a[k + j * a_dim1]
			;
	    }
	}
    }

    ret_val = 0;
    return ret_val;
} /* lurow_ */


integer ssrow_(integer *n, integer *lda, real *a, real *p, real *b)
{
    /* System generated locals */
    integer a_dim1, a_offset, ret_val, i__1, i__2;

    /* Local variables */
    static integer guarda_p__, i__, j;
    static real swap;


    /* Parameter adjustments */
    --b;
    --p;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	guarda_p__ = p[i__];
	swap = b[i__];
	b[i__] = b[guarda_p__];
	b[guarda_p__] = swap;
    }

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__ - 1;
	for (j = 1; j <= i__2; ++j) {
	    b[i__] -= b[j] * a[i__ + j * a_dim1];
	}
    }

    for (i__ = *n; i__ >= 1; --i__) {
	i__1 = *n;
	for (j = i__ + 1; j <= i__1; ++j) {
	    b[i__] -= b[j] * a[i__ + j * a_dim1];
	}
	b[i__] /= a[i__ + i__ * a_dim1];
    }

    ret_val = 0;
    return ret_val;
} /* ssrow_ */


integer lucol_(integer *n, integer *lda, real *a, real *p)
{
    /* System generated locals */
    integer a_dim1, a_offset, ret_val, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, imax;
    static real swap;


    /* Parameter adjustments */
    --p;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	imax = j;
	i__2 = *n;
	for (i__ = j + 1; i__ <= i__2; ++i__) {
	    if (a[i__ + j * a_dim1] > a[imax + j * a_dim1]) {
		imax = i__;
	    }
	}

	if (a[imax + j * a_dim1] == 0.f) {
	    ret_val = -1;
	    return ret_val;
	}

	if (imax != j) {
	    i__ = j;
	    i__2 = *n;
	    for (k = 1; k <= i__2; ++k) {
		swap = a[i__ + k * a_dim1];
		a[i__ + k * a_dim1] = a[imax + k * a_dim1];
		a[imax + k * a_dim1] = swap;
	    }
	}

	p[j] = (real) imax;

	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = i__ - 1;
	    for (k = 1; k <= i__3; ++k) {
		a[i__ + j * a_dim1] -= a[i__ + k * a_dim1] * a[k + j * a_dim1]
			;
	    }
	}

	if (a[j + j * a_dim1] == 0.f) {
	    ret_val = -1;
	    return ret_val;
	}

	i__2 = *n;
	for (i__ = j + 1; i__ <= i__2; ++i__) {
	    i__3 = j - 1;
	    for (k = 1; k <= i__3; ++k) {
		a[i__ + j * a_dim1] -= a[i__ + k * a_dim1] * a[k + j * a_dim1]
			;
	    }
	    a[i__ + j * a_dim1] /= a[j + j * a_dim1];
	}
    }

    ret_val = 0;
    return ret_val;
} /* lucol_ */


integer sscol_(integer *n, integer *lda, real *a, real *p, real *b)
{
    /* System generated locals */
    integer a_dim1, a_offset, ret_val, i__1, i__2;

    /* Local variables */
    static integer guarda_p__, i__, j;
    static real swap;


    /* Parameter adjustments */
    --b;
    --p;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	guarda_p__ = p[i__];
	swap = b[i__];
	b[i__] = b[guarda_p__];
	b[guarda_p__] = swap;
    }

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *n;
	for (i__ = j + 1; i__ <= i__2; ++i__) {
	    b[i__] -= b[j] * a[i__ + j * a_dim1];
	}
    }

    for (j = *n; j >= 1; --j) {
	b[j] /= a[j + j * a_dim1];
	for (i__ = j - 1; i__ >= 1; --i__) {
	    b[i__] -= b[j] * a[i__ + j * a_dim1];
	}
    }

    ret_val = 0;
    return ret_val;
} /* sscol_ */

/* Main program alias */ int lu_ () { MAIN__ (); return 0; }
