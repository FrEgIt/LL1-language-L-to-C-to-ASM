# LL(1) language

Implementation in C of a new language L that's have the supports of the Booleans operands MODULO '%' and GREATER THAN '>'.

For more details, see the links bellows:

https://en.wikipedia.org/wiki/Language

https://en.wikipedia.org/wiki/Group_theory

https://en.wikipedia.org/wiki/MIPS_architecture

https://en.wikipedia.org/wiki/Assembly_language

https://en.wikipedia.org/wiki/Formal_language

https://en.m.wikipedia.org/wiki/LL_grammar

## Documentation

This implementation is done with C11.

You can check the LL(1) specification in these files:

- Grammar : 			Grammaire LL(1) perso
- Firsts :				premier.csv
- Nexts: 				suivant.csv
- LL(1) table: 			Table LL(1) ok.csv

## Installation

Do on a terminal prompt:

- To compile:

```shell
$ make all
```

- To archive in tar.gz:

```shell
$ make tape
```

- To archive in ZIP:

```shell
$ make ZIP
```

-  lexically the source code file:

```shell
$ ./test_yylex -s "path-to-the-file-of-the-source-code.l"
```



```shell
$ ./test_yylex -s "path-to-the-file-of-the-source-code.l"
```



```shell
$ make clean
```

- To check and compile

```shell
$ make clean
```

- To check and compile

```shell
$ ./test_yylex -l "path-to-the-file-of-the-source-code.l"
```

- To check and compile lexically and syntactically the source code file:

```shell
$ ./test_yylex -s "path-to-the-file-of-the-source-code.l"
```

- To check and compile lexically and abstractly the source code file:

```shell
$ ./test_yylex -a "path-to-the-file-of-the-source-code.l"
```

- To check and compile lexically, abstractly and semantically the source code file :

```shell
$ ./test_yylex -t "path-to-the-file-of-the-source-code.l"
```

- To check and compile lexically, abstractly and semantically the source code file :

```shell
$ ./test_yylex -t "path-to-the-file-of-the-source-code.l"
```

- To check and compile lexically, abstractly, semantically and optimize the source code file to MIPS :

```shell
$ ./test_yylex -t "path-to-the-file-of-the-source-code.l"
```

## Authors

- Mohamed ABDELNABI
- David KACHKOCH
- Sylvain SENE

## License 

There is a CC-BY-SA's license. It's an open source project.
