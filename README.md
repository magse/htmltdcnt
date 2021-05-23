# htmltdcnt

A simple CLI tool for extracting data from regularised HTML tables.

**htmltdcnt** comes from a need to scanange on-line HTML tables of product data and material properties. The working principle is very simple, it traverse the raw HTML code of a file and each time it passes a complete cell (`</td>`) the currentlly stored content is printed out. Each time a end of row tag (`</tr>`) is passed a new line is printed out. Each table cell and row is counted and an optional indes is printed along the output as well. This index can be used for selecting just parts of a table using command line arguments.

The traversed HTML table need to be quite well-formed and regular in terms of shape. All rows need (almost) to have the same number of columns.

