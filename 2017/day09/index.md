<div>

<div>

# [Advent of Code](/) {#advent-of-code .title-global}

-   [\[About\]](/2017/about)
-   [\[Events\]](/2017/events)
-   [\[Shop\]](https://teespring.com/stores/advent-of-code){target="_blank"}
-   [\[Log In\]](/2017/auth/login)

</div>

<div>

#    [0xffff&]{.title-event-wrap}[2017](/2017)[]{.title-event-wrap} {#xffff2017 .title-event}

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
[Cheppers](https://cheppers.com/){target="_blank"
onclick="if(ga)ga('send','event','sponsor','sidebar',this.href);"
rel="noopener"} - xor(Pz0pQUI7Ch cmER8YDAEYAh4L GwEP, ↑↑↓↓←→←→BA)
:::
:::::
::::::

::: {role="main"}
## \-\-- Day 9: Stream Processing \-\--

A large stream blocks your path. According to the locals, it\'s not safe
to [cross the
stream]{title="\"Don't cross the streams!\", they yell, even though there's only one. They seem to think they're hilarious."}
at the moment because it\'s full of *garbage*. You look down at the
stream; rather than water, you discover that it\'s a *stream of
characters*.

You sit for a while and record part of the stream (your puzzle input).
The characters represent *groups* - sequences that begin with `{` and
end with `}`. Within a group, there are zero or more other things,
separated by commas: either another *group* or *garbage*. Since groups
can contain other groups, a `}` only closes the *most-recently-opened
unclosed group* - that is, they are nestable. Your puzzle input
represents a single, large group which itself contains many smaller
ones.

Sometimes, instead of a group, you will find *garbage*. Garbage begins
with `<` and ends with `>`. Between those angle brackets, almost any
character can appear, including `{` and `}`. *Within* garbage, `<` has
no special meaning.

In a futile attempt to clean up the garbage, some program has *canceled*
some of the characters within it using `!`: inside garbage, *any*
character that comes after `!` should be *ignored*, including `<`, `>`,
and even another `!`.

You don\'t see any characters that deviate from these rules. Outside
garbage, you only find well-formed groups, and garbage always terminates
according to the rules above.

Here are some self-contained pieces of garbage:

-   `<>`, empty garbage.
-   `<random characters>`, garbage containing random characters.
-   `<<<<>`, because the extra `<` are ignored.
-   `<{!>}>`, because the first `>` is canceled.
-   `<!!>`, because the second `!` is canceled, allowing the `>` to
    terminate the garbage.
-   `<!!!>>`, because the second `!` and the first `>` are canceled.
-   `<{o"i!a,<{i<a>`, which ends at the first `>`.

Here are some examples of whole streams and the number of groups they
contain:

-   `{}`, `1` group.
-   `{{{}}}`, `3` groups.
-   `{{},{}}`, also `3` groups.
-   `{{{},{},{{}}}}`, `6` groups.
-   `{<{},{},{{}}>}`, `1` group (which itself contains garbage).
-   `{<a>,<a>,<a>,<a>}`, `1` group.
-   `{{<a>},{<a>},{<a>},{<a>}}`, `5` groups.
-   `{{<!>},{<!>},{<!>},{<a>}}`, `2` groups (since all but the last `>`
    are canceled).

Your goal is to find the total score for all groups in your input. Each
group is assigned a *score* which is one more than the score of the
group that immediately contains it. (The outermost group gets a score of
`1`.)

-   `{}`, score of `1`.
-   `{{{}}}`, score of `1 + 2 + 3 = 6`.
-   `{{},{}}`, score of `1 + 2 + 2 = 5`.
-   `{{{},{},{{}}}}`, score of `1 + 2 + 3 + 3 + 3 + 4 = 16`.
-   `{<a>,<a>,<a>,<a>}`, score of `1`.
-   `{{<ab>},{<ab>},{<ab>},{<ab>}}`, score of `1 + 2 + 2 + 2 + 2 = 9`.
-   `{{<!!>},{<!!>},{<!!>},{<!!>}}`, score of `1 + 2 + 2 + 2 + 2 = 9`.
-   `{{<a!>},{<a!>},{<a!>},{<ab>}}`, score of `1 + 2 = 3`.

*What is the total score* for all groups in your input?

To play, please identify yourself via one of these services:

[\[GitHub\]](/auth/github) [\[Google\]](/auth/google)
[\[Twitter\]](/auth/twitter) [\[Reddit\]](/auth/reddit) [- [\[How Does
Auth Work?\]](/about#faq_auth)]{.quiet}
:::
