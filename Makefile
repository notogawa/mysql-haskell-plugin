all:
	ghc -c FFIInterpreter.hs -fPIC
	ghc -c hs_eval.cpp -fPIC `mysql_config --cflags`
	ghc -dynamic -fPIC -shared FFIInterpreter.hs hs_eval.o -optl-Wl,-soname -optl-Wl,hs_eval.so -o hs_eval.so -lHSrts-ghc7.4.1 -optl-Wl,-rpath,/usr/lib/ghc-7.4.1/
