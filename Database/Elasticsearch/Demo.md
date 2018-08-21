### Make sure it is running

```
curl http://localhost:9200/
```

### Show all indices on a cluster

```
curl  -XGET "http://localhost:9200/_cat/indices"
```

### Create an index

```
curl -XPUT "http://localhost:9200/news/" -d ' { "settings": { "number_of_shards": 3, "number_of_replicas": 0 } }'
```

### Check cluster health

```
curl -XGET "http://localhost:9200/_cluster/health?pretty"
```

### Delete an index

```
curl -XDELETE "http://localhost:9200/news
```

### Show settings of an index

```
curl -XGET "http://localhost:9200/news/_settings?pretty"
```

### Test analyzer with content

```
curl -XGET "http://localhost:9200/news/_analyze?pretty&analyzer=standard" -d '<html>heLLo,<title>this is a test</title><html>'
```

### Update the settigs of an index with a new analyzer

##### Clost the index

```
curl -XPOST "http://localhost:9200/news/_close"
```

##### Add the new analyzer

```
curl -XPUT "http://localhost:9200/news/_settings" -d '{ "analysis": { "char_filter": { "&_to_and": { "type": "mapping", "mappings": [ "&=> and "] }}, "filter": { "my_stopwords": { "type": "stop", "stopwords": [ "the", "a" ] }}, "analyzer": { "my_analyzer": { "type": "custom", "char_filter": [ "html_strip", "&_to_and" ], "tokenizer": "standard", "filter": [ "lowercase", "my_stopwords" ] }} }}}'
```

##### Open the index

```
curl -XPOST "http://localhost:9200/news/_open"
```

#### Check the analyzer is there

```
curl -XGET "http://localhost:9200/news/_settings?pretty"
```

#### Test the analyzer

```
curl -XGET "http://localhost:9200/news/_analyze?pretty&analyzer=my_analyzer" -d '<html>heLLo,<title>this is a test</title><html>'
```
