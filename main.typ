#import "dependency.typ": *
#import "template.typ": *

#show: ori.with(
    title: "ACM模板",
    author: "Arshtyi",
    subject: "ACM Templates",
    // semester: "2026 春",
    date: datetime.today(),
    // maketitle: true,
    first-line-indent: auto,
    font: font,
    // makeoutline: true,
    // outline-depth: 3,
    // size: 12pt,
    // theme: "dark",
    media: "print",
    lang: "en",
    // region: "cn",
)
#show: conf
#show: zebraw.with(
    lang: false,
    lang-font-args: font,
)

= Input & Output
== 关闭同步
#code("code/1/not_sync_with_stdio.cxx.txt", "cpp")
== 快读
#code("code/1/read.cxx.txt", "cpp")
== fread
#code("code/1/fread.cxx.txt", "cpp")
= Sort
== Quick Sort
时间复杂度$O(n log n)$
#code("code/2/quick_sort.cxx.txt", "cpp")
= Query
