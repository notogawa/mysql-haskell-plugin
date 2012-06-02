====================
mysql-haskell-plugin
====================

About
=====

MySQL User Defined Function to evaluate Haskell expression


Install
=======

::

  $ git clone git://github.com/notogawa/mysql-haskell-plugin.git
  $ cd mysql-haskell-plugin
  $ make
  $ mv hs_eval.so /where/to/mysql/plugin/directory
  $ mysql
  mysql> CREATE FUNCTION hs_eval RETURNS STRING SONAME 'hs_eval.so';


Usage
=====

::

  mysql> select hs_eval('sum [1 .. 10]');
  +--------------------------+
  | hs_eval('sum [1 .. 10]') |
  +--------------------------+
  | 55                       |
  +--------------------------+
  1 row in set (0.13 sec)

  mysql> select hs_eval('let fib = 1 : 1 : zipWith (+) fib (tail fib) in fib !! 10');
  +----------------------------------------------------------------------+
  | hs_eval('let fib = 1 : 1 : zipWith (+) fib (tail fib) in fib !! 10') |
  +----------------------------------------------------------------------+
  | 89                                                                   |
  +----------------------------------------------------------------------+
  1 row in set (0.05 sec)

