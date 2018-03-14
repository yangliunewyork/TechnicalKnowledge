

#### Test analyzer

```
curl -s -u username:password "HOST:PORT/INDEX_NAME/_analyze?pretty&analyzer=ANALYZER" 
-d '<html>heLLo,<title>this is a test</title><html>'
```

#### Update template

```
curl -s -u  username:password -XPUT "HOST:PORT/_template/TEMPLATE_NAME" -d @edg_mapping_pretty.json
```

#### Show all indices on a cluster

```
curl -s -u username:password "HOST:PORT/_cat/indices"
```

#### create an index

```
curl -s -u username:password -XPUT "HOST:PORT/INDEX_NAME" 
-d ' { "settings": { "number_of_shards": 3, "number_of_replicas": 2 } }'
```

#### Check cluster health

```
curl "164.55.92.127:9200/_health"
```

#### Check index status

```
curl "164.55.92.127:9200/nss_requests/_stats"
```

#### Count documents of an index

```
curl "164.55.92.127:9200/INDEX_NAME/_count"
```
