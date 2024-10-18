<div>

<div>

# [Advent of Code](/) {#advent-of-code .title-global}

-   [\[About\]](/2017/about)
-   [\[Events\]](/2017/events)
-   [\[Shop\]](https://teespring.com/stores/advent-of-code){target="_blank"}
-   [\[Log In\]](/2017/auth/login)

</div>

<div>

#        [λy.]{.title-event-wrap}[2017](/2017)[]{.title-event-wrap} {#λy.2017 .title-event}

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
[Formlabs](https://formlabs.com/){target="_blank"
onclick="if(ga)ga('send','event','sponsor','sidebar',this.href);"
rel="noopener"} - We make powerful, affordable 3D printers for
professionals.
:::
:::::
::::::

::: {role="main"}
## \-\-- Day 11: Hex Ed \-\--

Crossing the bridge, you\'ve barely reached the other side of the stream
when a program comes up to you, clearly in distress. \"It\'s my child
process,\" she says, \"he\'s gotten lost in an infinite grid!\"

Fortunately for her, you have plenty of experience with infinite grids.

Unfortunately for you, it\'s a [hex
grid](https://en.wikipedia.org/wiki/Hexagonal_tiling).

The hexagons (\"hexes\") in [this
grid]{title="Raindrops on roses and whiskers on kittens."} are aligned
such that adjacent hexes can be found to the north, northeast,
southeast, south, southwest, and northwest:

      \ n  /
    nw +--+ ne
      /    \
    -+      +-
      \    /
    sw +--+ se
      / s  \

You have the path the child process took. Starting where he started, you
need to determine the fewest number of steps required to reach him. (A
\"step\" means to move from the hex you are in to any adjacent hex.)

For example:

-   `ne,ne,ne` is `3` steps away.
-   `ne,ne,sw,sw` is `0` steps away (back where you started).
-   `ne,ne,s,s` is `2` steps away (`se,se`).
-   `se,sw,se,sw,sw` is `3` steps away (`s,s,sw`).

To play, please identify yourself via one of these services:

[\[GitHub\]](/auth/github) [\[Google\]](/auth/google)
[\[Twitter\]](/auth/twitter) [\[Reddit\]](/auth/reddit) [- [\[How Does
Auth Work?\]](/about#faq_auth)]{.quiet}
:::

--- Part Two ---
How many steps away is the furthest he ever got from his starting position?
