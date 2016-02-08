library("XML")

url <- read.csv("data.txt")[[1]]

len <- length(url)

print(len)

app_data <- data.frame()

for(i in 1:5){

	app <- htmlParse(url[[i]])

	title <- xmlValue(getNodeSet(app, "//h1")[[1]])
	value <- xmlValue(getNodeSet(app, "//div[@class='col-md-4 col-sm-3 center app_info_text1']")[[1]])
	rate <- length(getNodeSet(app, "//span[@class='glyphicon glyphicon-star']"))
	rate_count <- xmlValue(getNodeSet(app, "//div[@class='col-md-4 col-sm-3 center app_info_text1']")[[2]])
	rate_count <- gsub("	", "", rate_count)
	rate_count <- gsub("\n", "", rate_count)
	rate_count <- gsub("\\(", "", rate_count)
	rate_count <- gsub("\\)", "", rate_count)
	rate_count <- gsub(",", "", rate_count)
	rank <- xmlValue(getNodeSet(app, "//div[@class='col-xs-6 col-sm-3']/p[@class='ranking']")[[3]])
	category <- xmlValue(getNodeSet(app, "//div[@class='col-md-4']/div[@class='app_info_list']")[[1]])



	#url <- xmlGetAttr(array_url[[i]],"href")

	entry.frame <- (data.frame(title=title, value=value, rate=rate, rate_count=rate_count, rank=rank, category=category))
	app_data <- rbind(app_data, entry.frame)
}
write.table(app_data, "data.txt", quote=F, col.names=T, row.names=T, append=F, sep=", ")


print('fin')