# htmltdcnt

A simple CLI tool for extracting data from regularised HTML tables.

**htmltdcnt** comes from a need of scanning on-line HTML tables of product data and tabulated material properties. 

The working principle is very simple, **htmltdcnt** traverse the raw HTML code of a file and each time it passes a closing HTML tag (`</td>`) the currently stored content of a temporary textual buffer is printed out. Also, each time an end of row tag (`</tr>`) is passed a new line is printed out. Every identified table cell and row is counted and an optional index is printed along the output as well. This index can be used for selecting just parts of a table using command line arguments.

The traversed HTML table need to be quite well-formed and regular in terms of shape. All rows need (almost) to have the same number of columns.

The code is very rudimentary and does not handle all possible erroneous states in a good way so mind your use carefully. Comments and improvement suggestions are most welcome.

**htmltdcnt** have been tested and developed using some well known on-line pages like [mozilla table basics](https://developer.mozilla.org/en-US/docs/Learn/HTML/Tables/Basics), [w3schools tables](https://www.w3schools.com/html/html_tables.asp) and [w3schools CSS tables](https://www.w3schools.com/css/css_table.asp).

Other similair tools include:
- [openscraping-lib-csharp](https://github.com/microsoft/openscraping-lib-csharp)
- [html-table-extractor](https://github.com/yuanxu-li/html-table-extractor)
- [table2csv](https://github.com/hernamesbarbara/table2csv) (several projects exist called html2csv)

Enjoy table data!

