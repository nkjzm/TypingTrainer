library("XML")

for(j in 1:100){

  url <- paste("http://ejje.weblio.jp/sentence/content/%E3%81%82/",j,sep="")

  html <- htmlParse(url)
  data <- data.frame()

  #英文が含まれるclass要素を取得
  array_div <- getNodeSet(html, "//p[@class='qotCJE']")
  len <- length(array_div)

  for(i in 2:len){

    #正規表現で抽出・整形
    sentense <- xmlValue(array_div[[i]])
    sentense <- gsub("\n", "", sentense)
    sentense <- gsub("\"", "", sentense)
    sentense <- gsub("(<!--.*?$)", "", sentense)
    sentense <- gsub("(-.*?$)", "", sentense)
    sentense <- gsub("( ^[a-zA-Z])", "", sentense)
    sentense <- gsub("( $)", "", sentense)
    sentense <- gsub(" ", "", sentense)
    sentense <- gsub("'", "", sentense)
    sentense <- gsub("`", "", sentense)
    sentense <- gsub("([^\x01-\x7E])", "", sentense)

    #英文をデータに追加
    if(sentense != ""){
      print(sentense)
      entry.frame <- (data.frame(sentense=sentense))
      data <- rbind(data, entry.frame)
    }
  }
  #データをファイルに追加書き込み
  write.table(data, "data.txt", quote=F,col.names=F, row.names=F, append=T, sep="")

}

print('fin!')