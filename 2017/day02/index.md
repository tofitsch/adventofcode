<div>

<div>

# [Advent of Code](/) {#advent-of-code .title-global}

-   [\[About\]](/2017/about)
-   [\[Events\]](/2017/events)
-   [\[Shop\]](https://teespring.com/stores/advent-of-code){target="_blank"}
-   [\[Log In\]](/2017/auth/login)

</div>

<div>

#  [{\'year\':]{.title-event-wrap}[2017](/2017)[}]{.title-event-wrap} {#year2017 .title-event}

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
[Winton](http://winton.com/){target="_blank"
onclick="if(ga)ga('send','event','sponsor','sidebar',this.href);"
rel="noopener"} - a data science and investment management company
:::
:::::
::::::

::: {role="main"}
## \-\-- Day 2: Corruption Checksum \-\--

As you walk through the door, a glowing humanoid shape yells in your
direction. \"You there! Your state appears to be idle. Come help us
repair the corruption in this spreadsheet - if we take another
millisecond, we\'ll have to display an hourglass cursor!\"

The spreadsheet consists of rows of apparently-random numbers. To make
sure the recovery process is on the right track, they need you to
calculate the spreadsheet\'s *checksum*. For each row, determine the
difference between the largest value and the smallest value; the
checksum is the sum of all of these differences.

For example, given the following spreadsheet:

    5 1 9 5
    7 5 3
    2 4 6 8

-   The first row\'s largest and smallest values are `9` and `1`, and
    their difference is `8`.
-   The second row\'s largest and smallest values are `7` and `3`, and
    their difference is `4`.
-   The third row\'s difference is `6`.

In this example, the spreadsheet\'s checksum would be `8 + 4 + 6 = 18`.

*What is the checksum* for the spreadsheet in your puzzle input?

To play, please identify yourself via one of these services:

[\[GitHub\]](/auth/github) [\[Google\]](/auth/google)
[\[Twitter\]](/auth/twitter) [\[Reddit\]](/auth/reddit) [- [\[How Does
Auth Work?\]](/about#faq_auth)]{.quiet}
:::

Great work; looks like we're on the right track after all. Here's a star for your effort." However, the program seems a little worried. Can programs be worried?

"Based on what we're seeing, it looks like all the User wanted is some information about the evenly divisible values in the spreadsheet. Unfortunately, none of us are equipped for that kind of calculation - most of us specialize in bitwise operations."

It sounds like the goal is to find the only two numbers in each row where one evenly divides the other - that is, where the result of the division operation is a whole number. They would like you to find those numbers on each line, divide them, and add up each line's result.

For example, given the following spreadsheet:

5 9 2 8
9 4 7 3
3 8 6 5
In the first row, the only two numbers that evenly divide are 8 and 2; the result of this division is 4.
In the second row, the two numbers are 9 and 3; the result is 3.
In the third row, the result is 2.
In this example, the sum of the results would be 4 + 3 + 2 = 9.

What is the sum of each row's result in your puzzle input?
