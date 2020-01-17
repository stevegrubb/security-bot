#!/usr/bin/env -S r -L /home/sgrubb/R/x86_64-redhat-linux-gnu-library/3.6

library("XML")
library("data.tree")
#library("networkD3")

# Point to our aiml dir
setwd("/home/sgrubb/test/security-bot-2/aiml_set/security/")

# Put all patterns as strings in single column.
xmldataframe <- xmlToDataFrame("selinux.aiml")
text <- as.data.frame(na.omit(xmldataframe$pattern), stringsAsFactors=FALSE)

# Convert it into a hierarchial tree structure
text$pathString <- do.call(paste, c("cmd", sep=" ", text[1]))
ts <- as.Node(text, pathDelimiter = " ")
print(ts)

# And now as a hierarchial list
#hl <- ToListExplicit(ts, unname = TRUE)

# And visualize it
#diagonalNetwork(List = hl)

