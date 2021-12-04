# Bank (DSA Counrse Project)

**Objective:**Assume that you own a Bank having 10 ATMs in a city. Design a Banking solution in
C++ using all the features including STLs to mimic a real life bank.

## Table of contents

- [General info](#general-info)
- [Technologies](#technologies)
- [Setup](#setup)

## General info

Bank works in two modes:

1. BANKING MODE
2. ATM MODE
   to swich use command **Z**

<details><summary>BANKING MODE</summary>
<p>
| Command | Description |
| --- | --- |
| S | open bank |
| O | open an account |
| B | balance enquiry |
| W | withdrawal |
| D | deposit |
| C | close account |
| A | activate ATM |
| U | unlock ATM |
| P | print all accounts |
| I | apply interest to all accounts |
| E | exit and close all accounts |
</p>
</details>
<details><summary>ATM MODE</summary>
<p>
| Command | Description |
| --- | --- |
| X | PIN change |
| F | fund transfer |
| B | balance enquiry |
| W | withdrawal |
| M | mini statement |
</p>
</details>

It saves data from preveous execution and can load all info on the next execution.

## Technologies

Project uses:

- C++
- GNU Make
