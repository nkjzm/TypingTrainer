library("XML")

for(j in 1:999){

url <- paste("http://ejje.weblio.jp/sentence/content/%E3%81%82/",j,sep="")

ranking <- htmlParse(url)
#ranking <- htmlParse("/Users/Kohki/Desktop/App StoreのiPhoneのすべてのカテゴリのトップセールスアプリランキング400 - Top App Ranking 400.html")
ranking_data <- data.frame()

len <- length(getNodeSet(ranking, "//p[@class='qotCJE']"))
print(len)

array_div	<- getNodeSet(ranking, "//p[@class='qotCJE']")

print("--------ここからループ")

for(i in 2:len){

  #title <- xmlValue(array_title[[i]])
  #url <- xmlGetAttr(array_div[[i]],"href")
  url <- xmlValue(array_div[[i]])
  url <- gsub("\n", "", url)
  url <- gsub("\"", "", url)
  url <- gsub("(<!--.*?$)", "", url)
  url <- gsub("(-.*?$)", "", url)
  url <- gsub("( ^[a-zA-Z])", "", url)
  url <- gsub("( $)", "", url)
  url <- gsub(" ", "", url)
  url <- gsub("'", "", url)
  url <- gsub("`", "", url)
  url <- gsub("([^\x01-\x7E])", "", url)


  if(url != ""){

  print(url)

  entry.frame <- (data.frame(url=url))
  ranking_data <- rbind(ranking_data, entry.frame)

}
}
write.table(ranking_data, "data.txt", quote=F,col.names=F, row.names=F, append=T, sep="")


}

print('fin!')