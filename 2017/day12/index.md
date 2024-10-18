<div>

<div>

# [Advent of Code](/) {#advent-of-code .title-global}

-   [\[About\]](/2017/about)
-   [\[Events\]](/2017/events)
-   [\[Shop\]](https://teespring.com/stores/advent-of-code){target="_blank"}
-   [\[Log In\]](/2017/auth/login)

</div>

<div>

#   [{:year ]{.title-event-wrap}[2017](/2017)[}]{.title-event-wrap} {#year-2017 .title-event}

-   [\[Calendar\]](/2017)
-   [\[AoC++\]](/2017/support)
-   [\[Sponsors\]](/2017/sponsors)
-   [\[Leaderboard\]](/2017/leaderboard)
-   [\[Stats\]](/2017/stats)

</div>

</div>

:::::: {#sidebar}
::::: {#sponsor}
::: quiet
Our [sponsors](/2017/sponsors) help make Advent of Code possible:
:::

::: sponsor
[Infi](https://aoc.infi.nl/){target="_blank"
onclick="if(ga)ga('send','event','sponsor','sidebar',this.href);"
rel="noopener"} - Onze puzzel is onmogelijk te kraken. Behalve voor
echte nerds.
:::
:::::
::::::

::: {role="main"}
## \-\-- Day 12: Digital Plumber \-\--

Walking along the memory banks of the stream, you find a small village
that is experiencing a little confusion: some programs can\'t
communicate with each other.

Programs in this village communicate using a fixed system of *pipes*.
Messages are passed between programs using these pipes, but most
programs aren\'t connected to each other directly. Instead, programs
pass messages between each other until the message reaches the intended
recipient.

For some reason, though, some of these messages aren\'t ever reaching
their intended recipient, and the programs suspect that some
[pipes]{title="Yes, citizens, plumbing! It's the latest invention to hit Rome!"}
are missing. They would like you to investigate.

You walk through the village and record the ID of each program and the
IDs with which it can communicate directly (your puzzle input). Each
program has one or more programs with which it can communicate, and
these pipes are bidirectional; if `8` says it can communicate with `11`,
then `11` will say it can communicate with `8`.

You need to figure out how many programs are in the group that contains
program ID `0`.

For example, suppose you go door-to-door like a travelling salesman and
record the following list:

    0 <-> 2
    1 <-> 1
    2 <-> 0, 3, 4
    3 <-> 2, 4
    4 <-> 2, 3, 6
    5 <-> 6
    6 <-> 4, 5

In this example, the following programs are in the group that contains
program ID `0`:

-   Program `0` by definition.
-   Program `2`, directly connected to program `0`.
-   Program `3` via program `2`.
-   Program `4` via program `2`.
-   Program `5` via programs `6`, then `4`, then `2`.
-   Program `6` via programs `4`, then `2`.

Therefore, a total of `6` programs are in this group; all but program
`1`, which has a pipe that connects it to itself.

*How many programs* are in the group that contains program ID `0`?

To play, please identify yourself via one of these services:

[\[GitHub\]](/auth/github) [\[Google\]](/auth/google)
[\[Twitter\]](/auth/twitter) [\[Reddit\]](/auth/reddit) [- [\[How Does
Auth Work?\]](/about#faq_auth)]{.quiet}
:::
