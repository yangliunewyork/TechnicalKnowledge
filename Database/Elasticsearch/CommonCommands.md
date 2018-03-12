#### Test analyzer


curl -s -u username:credential "esgen01deva04:9800/news_yearly_2018_old_analysis_created_20170227_093100_by_mihuynh/_analyze?pretty&analyzer=html_news_stemming_with_case" -d '<html>heLLo,<title>this is a test</title><html>'
