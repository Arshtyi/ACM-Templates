#import "dependency.typ": *

#let font = (
    main: "IBM Plex Serif",
    mono: "Maple Mono NF",
    cjk: "Source Han Serif SC",
    emph-cjk: "Source Han Serif SC",
    math: "New Computer Modern Math",
    math-cjk: "Source Han Serif SC",
)

#let conf(body) = {
    set heading(
        numbering: numbly(
            "{1:I} ",
            "{2:1} ",
            "{2}.{3:i} ",
        ),
    )
    show heading.where(level: 1): set align(center)
    body
}
#let code(path, lang) = {
    raw(block: true, read(path), lang: lang)
}
