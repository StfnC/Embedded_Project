# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à états finis logicielles
+ Section #  : 3
+ Équipe #   : 71
+ Correcteur : Charles Jiang

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |    -0.5        |
| __Résultat partiel__                         | __(1/1.5)__ |

pb2: le state de l'état ne devrait pas être sa sortie (couleur), il devrait représenter le progrès

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (/0.5)     |
| Noms de variables décrivent l'intention      | (/0.5)     |
| Noms de fonctions décrivent l'intention      | (/0.5)     |
| etc                                             -0.1
| __Résultat partiel__                         | __(1.4/1.5)__ |

(-0.1) valeur double assignee doit avoir point décimal 10 -> 10.0

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1/1.0)__ |


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (/0.5)     |
| Indentation uniforme dans le programme       | (/0.5)     |
| __Résultat partiel__                         | __(1/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(1/1.0)__ |

bonne utilisation des fonctions, bravo!


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(4/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (/1.5)     |
| Absence de fichiers inutiles                 | (/1.5)     |
| __Résultat partiel__                         | __(3/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (/1.5)     |
| Absence de messages d'attention (*warning*)  | (/0.5)     |
| __Résultat partiel__                         | __(2/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (/2.5)     |
| Cas limites observables                      | (/2.5)     |
| __Résultat partiel__                         | __(5/5.0)__ |

# Résultat

__Total des points: 19.4/20__

# Commentaires du correcteur:



# Basé sur le commit suivant
```
commit 0b8eeb920e60c46b4cb8fb28e249d91e139a2eef
Author: Stefan Cotargasanu <stefan.cotargasanu@polymtl.ca>
Date:   Mon Jan 31 15:44:52 2022 -0500

    Modifié le code pour l'adapter aux interrupts
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/71/tp/tp2/pb1 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c pb1.cpp
avr-gcc -Wl,-Map,pb1.elf.map -mmcu=atmega324pa -o pb1.elf  pb1.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex pb1.elf pb1.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/71/tp/tp2/pb1 »

```

## Sortie de `make` dans `tp/tp2/pb2`
```
make : on entre dans le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/71/tp/tp2/pb2 »
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c pb2.cpp
avr-gcc -Wl,-Map,pb2.elf.map -mmcu=atmega324pa -o pb2.elf  pb2.o \
-lm 
avr-objcopy -j .text -j .data \
	-O ihex pb2.elf pb2.hex
make : on quitte le répertoire « /home/gigl/Documents/inf1900-grader/correction_tp2/71/tp/tp2/pb2 »

```
