<div>

<div>

# [Advent of Code](/) {#advent-of-code .title-global}

-   [\[About\]](/2017/about)
-   [\[Events\]](/2017/events)
-   [\[Shop\]](https://teespring.com/stores/advent-of-code){target="_blank"}
-   [\[Log In\]](/2017/auth/login)

</div>

<div>

#   [0.0.0.0:]{.title-event-wrap}[2017](/2017)[]{.title-event-wrap} {#section .title-event}

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
[Kx Systems](http://kx.com/){target="_blank"
onclick="if(ga)ga('send','event','sponsor','sidebar',this.href);"
rel="noopener"} - kdb+, the in-memory time series technology standard
:::
:::::
::::::

::: {role="main"}
## \-\-- Day 8: I Heard You Like Registers \-\--

You receive a [signal]{title="There's that sorcery I told you about."}
directly from the CPU. Because of your recent assistance with [jump
instructions](5), it would like you to compute the result of a series of
unusual register instructions.

Each instruction consists of several parts: the register to modify,
whether to increase or decrease that register\'s value, the amount by
which to increase or decrease it, and a condition. If the condition
fails, skip the instruction without modifying the register. The
registers all start at `0`. The instructions look like this:

    b inc 5 if a > 1
    a inc 1 if b < 5
    c dec -10 if a >= 1
    c inc -20 if c == 10

These instructions would be processed as follows:

-   Because `a` starts at `0`, it is not greater than `1`, and so `b` is
    not modified.
-   `a` is increased by `1` (to `1`) because `b` is less than `5` (it is
    `0`).
-   `c` is decreased by `-10` (to `10`) because `a` is now greater than
    or equal to `1` (it is `1`).
-   `c` is increased by `-20` (to `-10`) because `c` is equal to `10`.

After this process, the largest value in any register is `1`.

You might also encounter `<=` (less than or equal to) or `!=` (not equal
to). However, the CPU doesn\'t have the bandwidth to tell you what all
the registers are named, and leaves that to you to determine.

*What is the largest value in any register* after completing the
instructions in your puzzle input?

To play, please identify yourself via one of these services:

[\[GitHub\]](/auth/github) [\[Google\]](/auth/google)
[\[Twitter\]](/auth/twitter) [\[Reddit\]](/auth/reddit) [- [\[How Does
Auth Work?\]](/about#faq_auth)]{.quiet}
:::

--- Part Two ---
To be safe, the CPU also needs to know the highest value held in any register during this process so that it can decide how much memory to allocate to these operations. For example, in the above instructions, the highest value ever held was 10 (in register c after the third instruction was evaluated).
