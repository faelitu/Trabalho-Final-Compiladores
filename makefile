simples : utils.c tree.c lexico.l sintatico.y;\
		flex -o lexico.c lexico.l;\
		bison -o sintatico.c sintatico.y -v -d;\
		gcc -o simples utils.c tree.c lexico.c sintatico.c

limpa : ;\
		rm -f lexico.c sintatico.c sintatico.output *- sintatico.h simples\