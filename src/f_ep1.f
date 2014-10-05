      program LU
c
c
c     Matriz LU
c
      implicit none
      integer lurow, ssrow, iargc
      integer lucol, sscol
      integer i, j, k, n, nmax, argc
      parameter(nmax=1000) 
      double precision num
      double precision A(nmax, nmax), b(nmax), p(nmax)
      character nome_arquivo*20, orientacao*6
c
      argc = iargc()
      if (argc > 1) then
        call getarg(1, nome_arquivo)
        call getarg(2, orientacao)
      else
        print *, "Digite o nome do arquivo e se e orientada a linha ou c
     &oluna. (Ex: m1.dat linha)"
        call exit
      end if
c
      open(unit=1, file=nome_arquivo, status='old')
c
      read(1,*) n
      do k=1,(n**2)
        read(1,*) i, j, num
        A(i+1, j+1) = num
      end do
c
      do k=1,n
        read(1,*) i, num
        b(i+1) = num
      end do
c
      close(1)
c
c======================================================
c     OPERACAO POR LINHA
c
      if (orientacao == 'linha' .AND.
     &    lurow(n, nmax, A, p) == -1) then
        print *, "Matriz singular."
        call exit
      end if
      if (orientacao == 'linha' .AND.
     &    ssrow(n, nmax, A, p, b) == -1) then
        print *, "Matriz singular."
        call exit
      end if
c======================================================
c     OPERACAO POR COLUNA
c
      if (orientacao == 'coluna' .AND.
     &    lucol(n, nmax, A, p) == -1) then
        print *, "Matriz singular."
        call exit
      end if
      if (orientacao == 'coluna' .AND.
     &    sscol(n, nmax, A, p, b) == -1) then
        print *, "Matriz singular."
        call exit
      end if
c======================================================
c
      do i=1,n
        print *, b(i)
      end do
c
      end
c
      integer function lurow(n, lda, A, p)
        implicit none
        integer n, i, j, k, imax, lda
        double precision A(lda, lda), p(lda), swap
c
        do i=1,n
          imax = i
          j = i
          do k=i+1,n
            if (A(k, j) > A(imax, j)) then
              imax = k
            end if
          end do
c
          if (A(imax, j) == 0) then
            lurow = -1
            return
          end if
c
          if (imax /= i) then
            do j=1,n
              swap = (A(i, j))
              A(i, j) = A(imax, j)
              A(imax, j) = swap
            end do
          end if
c
          p(i) = imax
c
          do j=1,i-1
            if (A(j, j) == 0) then
              lurow = -1
              return
            end if
c
            do k=1,j-1
              A(i, j) = A(i, j) - A(i, k)*A(k, j)
            end do
            A(i, j) = A(i, j)/A(j, j)
          end do
c
          do j=i,n
            do k=1,i-1
              A(i, j) = A(i, j) - A(i, k)*A(k, j)
            end do
          end do
        end do
c
        lurow = 0
        return
      end
c
      integer function ssrow(n, lda, A, p, b)
        implicit none
        integer n, i, j, guarda_p, lda
        double precision A(lda, lda), p(lda), b(lda), swap
c
        do i=1,n
          guarda_p = p(i)
          swap = b(i)
          b(i) = b(guarda_p)
          b(guarda_p) = swap
        end do
c
        do i=1,n
          do j=1,i-1
            b(i) = b(i) - b(j)*A(i, j)
          end do
        end do
c
        do i=n,1,-1
          do j=i+1,n
            b(i) = b(i) - b(j)*A(i, j)
          end do
          b(i) = b(i)/A(i, i)
        end do
c
        ssrow = 0
        return
      end
c
      integer function lucol(n, lda, A, p)
        implicit none
        integer n, i, j, k, imax, lda
        double precision A(lda, lda), p(lda), swap
c
        do j=1,n
          imax = j
          do i=j+1,n
            if (A(i, j) > A(imax, j)) then
              imax = i
            end if
          end do
c
          if (A(imax, j) == 0) then
            lucol = -1
            return
          end if
c
          if (imax /= j) then
            i = j
            do k=1,n
              swap = A(i, k)
              A(i, k) = A(imax, k)
              A(imax, k) = swap
            end do
          end if
c
          p(j) = imax
c
          do i=1,j
            do k=1,i-1
              A(i, j) = A(i, j) - A(i, k)*A(k, j)
            end do
          end do
c
          if (A(j, j) == 0) then
            lucol = -1
            return
          end if
c
          do i=j+1,n
            do k=1,j-1
              A(i, j) = A(i, j) - A(i, k)*A(k, j)
            end do
            A(i, j) = A(i, j)/A(j, j)
          end do          
        end do
c
        lucol = 0
        return
      end
c
      integer function sscol(n, lda, A, p, b)
        implicit none
        integer n, i, j, guarda_p, lda
        double precision A(lda, lda), p(lda), b(lda), swap
c
        do i=1,n
          guarda_p = p(i)
          swap = b(i)
          b(i) = b(guarda_p)
          b(guarda_p) = swap
        end do
c
        do j=1,n
          do i=j+1,n
            b(i) = b(i) - b(j)*A(i, j)
          end do
        end do
c
        do j=n,1,-1
          b(j) = b(j)/A(j, j)
          do i=j-1,1,-1
            b(i) = b(i) - b(j)*A(i, j)
          end do
        end do
c
        sscol = 0
        return
      end
