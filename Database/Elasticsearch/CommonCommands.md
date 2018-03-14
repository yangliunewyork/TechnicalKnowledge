

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
