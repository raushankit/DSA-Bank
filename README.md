# Bank (DSA Course Project)

**Objective:** Assume that you own a Bank having 10 ATMs in a city. Design a Banking solution in
C++ using all the features including STLs to mimic a real life bank.

## Table of contents

- [General info](#general-info)
- [Technologies](#technologies)
- [Setup](#setup)

## General info

Bank works in two modes:

1. [BANKING Mode](#banking-mode)
2. [ATM Mode](#ATM-mode)

to switch between the modes **_use command Z_**

### BANKING Mode

| Command | Description                    |
| ------- | ------------------------------ |
| S       | open bank                      |
| O       | open an account                |
| B       | balance enquiry                |
| W       | withdrawal                     |
| D       | deposit                        |
| C       | close account                  |
| A       | activate ATM                   |
| U       | unlock ATM                     |
| P       | print all accounts             |
| I       | apply interest to all accounts |
| E       | exit and close all accounts    |

### ATM Mode

| Command | Description     |
| ------- | --------------- |
| X       | PIN change      |
| F       | fund transfer   |
| B       | balance enquiry |
| W       | withdrawal      |
| M       | mini statement  |

**_It also saves data from preveous execution and can load all info on the next execution_**

## Technologies

Project uses:

- C++
- GNU Make

## Setup

- clone project

```
git clone https://github.com/raushankit/DSA-Bank.git
```

- to run project

```make
cd src
make run
```

> > or

```
cd src
make
./a.out
```
