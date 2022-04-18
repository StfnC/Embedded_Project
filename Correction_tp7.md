# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Mise en commun du code et formation de librairies
+ Section #  : 3
+ Équipe #   : 5471
+ Correcteur : Charles Jiang

# CODE

| Points importants                                        | Poids       |
| -------------------------------------------------------- | ----------- |
| La qualités et le choix de vos portions de code choisies | (4.75/5.0)      |
| La qualités de vos modifications aux Makefiles           | (4.75/5.0)      |
| __Résultat partiel__                                     | __(9.5/10.0)__ |

## **PORTION DE CODE**
- mettre les #include generalement dans les .h
-.25 const uint16_t ONE_SECOND_PRESCALER_VALUE = 7812.5; est plutot un double et non uint16_t

Excellent travail tres impressionnant! Belle utilisation de classes et de fonctions!

## **Makefile**

makefile lib:
 conseil : vous pouvez utiliser PRJSRC=$(wildcard *.cpp) pour eviter de rajouter chaque cpp au makefile 
-0.25 il faut specifier le compilateur (avr-ar) au lieu de seulement ar

# RAPPORT

| Points importants                                                           | Poids      |
| --------------------------------------------------------------------------- | ---------- |
| Explications cohérentes par rapport au code retenu pour former la librairie | (/2.0)     |
| Explications cohérentes par rapport aux Makefiles modifiés                  | (1.75/2.0)     |
| Explications claires avec un bon niveau de détails                          | (/2.0)     |
| Bon français                                                                | (/1.0)     |
| __Résultat partiel__                                                        | __(6.75/7.0)__ |

-0.25 manque expliquation DEBUG dans makefile
belle explication dans le rapport

# GÉNÉRALITÉS
## Bonne soumission de l'ensemble du code et du rapport selon le format demandé 

| Pénalité par erreur      | -0.5       |
| ------------------------ | ---------- |
| compilation sans erreurs |            |
| etc                      |            |
| __Résultat partiel__     | __(2.5/3.0)__ |

-0.5 warning dans lib (led.cpp)

# Résultat

__Total des points: 18.75/20__

# Commentaires du correcteur:

À remplir par l'évaluateur


# Basé sur le commit suivant
```
commit 4a29ec11cafdd4a38447709ddd9bacdf370891e2
Author: Stefan Cotargasanu <cotargasanu.stef@gmail.com>
Date:   Sun Mar 13 16:54:57 2022 -0400

    Added testing of the library
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp7/lib`
```
make : on entre dans le répertoire « /home/gigl/Documents/2022/inf1900-grader/correction_tp7/5471/tp/tp7/lib »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c can.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c memoire_24.cpp
memoire_24.cpp:30:3: warning: #warning "F_CPU pas defini pour 'memoire_24.cpp'" [-Wcpp]
   30 | # warning "F_CPU pas defini pour 'memoire_24.cpp'"
      |   ^~~~~~~
In file included from memoire_24.cpp:34:
memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
memoire_24.cpp: In member function 'uint8_t Memoire24CXXX::lecture(uint16_t, uint8_t*, uint8_t)':
memoire_24.cpp:280:7: warning: this 'while' clause does not guard... [-Wmisleading-indentation]
  280 |       while ((TWCR & _BV(TWINT)) == 0) ; // Attente de fin de transmission
      |       ^~~~~
memoire_24.cpp:281:10: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the 'while'
  281 |          *donnee++ = TWDR;               // Lecture
      |          ^
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c MotorsController.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c usart.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c led.cpp
In file included from led.cpp:12:
/usr/avr/include/util/delay.h:92:3: warning: #warning "F_CPU not defined for <util/delay.h>" [-Wcpp]
   92 | # warning "F_CPU not defined for <util/delay.h>"
      |   ^~~~~~~
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c interruptions.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c counter.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c debug.cpp
ar -crs librene.a  can.o memoire_24.o MotorsController.o usart.o led.o interruptions.o counter.o debug.o
make : on quitte le répertoire « /home/gigl/Documents/2022/inf1900-grader/correction_tp7/5471/tp/tp7/lib »

```

## Sortie de `make` dans `tp/tp7/exec`
```
make : on entre dans le répertoire « /home/gigl/Documents/2022/inf1900-grader/correction_tp7/5471/tp/tp7/exec »
avr-gcc -I. -I/usr/include/simavr  -MMD -I ../lib/ -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c lib_test.cpp
avr-gcc -Wl,-Map,lib_test.elf.map -mmcu=atmega324pa -o lib_test.elf  lib_test.o \
-lm -l rene -L ../lib/
avr-objcopy -j .text -j .data \
	-O ihex lib_test.elf lib_test.hex
make : on quitte le répertoire « /home/gigl/Documents/2022/inf1900-grader/correction_tp7/5471/tp/tp7/exec »

```
