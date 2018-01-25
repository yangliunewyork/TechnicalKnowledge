This is a quick tutorial to have fun with Logstash and Filebeat.

Logstash is an open source, server-side data processing pipeline that ingests data from a multitude of sources simultaneously, transforms it, and then sends it to your favorite “stash.”

https://www.elastic.co/products/logstash

Filebeat is a log data shipper for local files. Installed as an agent on your servers, Filebeat monitors the log directories or specific log files, tails the files, and forwards them either to Elasticsearch or Logstash for indexing.

https://www.elastic.co/guide/en/beats/filebeat/current/filebeat-overview.html

# Download and Install

#### Download and install Logstash:

```
wget https://artifacts.elastic.co/downloads/logstash/logstash-6.1.1.tar.gz
tar xvzf logstash-6.1.1.tar.gz
```

#### Download and install filebeat:

```
wget "https://artifacts.elastic.co/downloads/beats/filebeat/filebeat-6.1.1-linux-x86_64.tar.gz"

tar xvzf filebeat-6.1.1-linux-x86_64.tar.gz
```

# Fun time

### Configuring Filebeat to Send Log Lines to Logstash

Before you create the Logstash pipeline, you’ll configure Filebeat to send log lines to Logstash. The Filebeat client is a lightweight, resource-friendly tool that collects logs from files on the server and forwards these logs to your Logstash instance for processing. Filebeat is designed for reliability and low latency. 

After installing Filebeat, you need to configure it. Open the ```filebeat.yml``` file located in your Filebeat installation directory, and replace the contents similar to following lines. Make sure paths points to the files you want to parse.

```
filebeat.prospectors:
- type: log
  paths:
    - /path/to/file/logstash-tutorial.log  # Any non-binary file 
output.logstash:
  hosts: ["localhost:5044"]
```  

To keep the configuration simple, you won’t specify TLS/SSL settings as you would in a real world scenario.

At the data source machine, run Filebeat with the following command:

```
sudo ./filebeat -e -c filebeat.yml -d "publish"
```

### Configuring Logstash for Filebeat Input

Next, you create a Logstash configuration pipeline that uses the Beats input plugin to receive events from Beats.

The following text represents the skeleton of a configuration pipeline:

```
input {
    beats {
        port => "5044"
    }
}
 filter {
    grok {
        match => { "message" => "%{COMBINEDAPACHELOG}"}
    }
    geoip {
        source => "clientip"
    }
}
output {
    stdout { codec => rubydebug }
}
```

Let's run log-stash:  

```
bin/logstash -f first-pipeline.conf --config.reload.automatic --path.data data-unixdeva16
```

### Logstash patterns

Logstash supports customized patterns.

You can test your pattern on this website : http://grokdebug.herokuapp.com/.


### Using grok and mutate to type your data

Logstash is an event processing pipeline, which features a rich ecosystem of plugins, allowing users to push data in, manipulate it, and then send it to various backends.

One of those plugins is [grok](https://www.elastic.co/guide/en/logstash/current/plugins-filters-grok.html). Grok is currently the best for Logstash to parse unstructured log data and structure it so it can be best queried by Elasticsearch. [Mutate](https://www.elastic.co/guide/en/logstash/current/plugins-filters-mutate.html), another popular plugin, allows the user to manipulate Logstash event data in many useful ways.

##### Why type my data?

Elasticsearch is so much more powerful than just its full-text search use case. It can also calculate a variety of statistics on numerical data in near real-time. Kibana can then take the results of these calculations and plot them in charts and dashboards. If the data is not typed properly, Elasticsearch will be unable to perform these calculations. Typing your data properly takes a little thought and effort, but yields amazing results!

##### JSON, Strings, and Numbers

All documents sent to Elasticsearch must be in JSON format, but Logstash takes care of transforming your data into JSON documents for you. When Elasticsearch receives a JSON document, it will do its best to try to guess what type of data each field contains. The list of core types and a thorough description of each one can be found here.

If I were to send the following JSON document to Elasticsearch (patterned as a Logstash event):

```
{
    "@timestamp": "2014-10-07T20:11:45.000Z",
    "@version": "1",
    "count": 2048,
    "average": 1523.33,
    "host": "elasticsearch.com"
}
```

We can see 5 fields: @timestamp, @version, count, average, and host.

In the JSON I am sending, @timestamp and host are string fields, count and average are numeric fields, but @version is a strange hybrid. The value of @version is a number, but because it is inside double quotes " it means that it is considered a string within this JSON document.

If I were to send this document to Elasticsearch to be indexed:

```
curl -XPOST localhost:9200/Logstash-2014.10.07/logs/1 -d '
{
    "@timestamp": "2014-10-07T20:11:45.000Z",
    "@version": "1",
    "count": 2048,
    "average": 1523.33,
    "host": "elasticsearch.com"
}
```

and then check the mapping…

```
curl localhost:9200/Logstash-2014.10.07/_mapping?pretty
{
  "Logstash-2014.10.07" : {
    "mappings" : {
      "logs" : {
        "properties" : {
          "@timestamp" : {
            "type" : "date",
            "format" : "dateOptionalTime"
          },
          "@version" : {
            "type" : "string"
          },
          "average" : {
            "type" : "double"
          },
          "count" : {
            "type" : "long"
          },
          "host" : {
            "type" : "string"
          }
        }
      }
    }
  }
}
```

average is type double, count is type long, Elasticsearch successfully guessed that @timestamp is a date field, and host is type string.

Because @version was sent as a string, it remains type string.

It is important to understand that unless you type (or cast) your data accordingly, Logstash sends all values to Elasticsearch as strings.

### Coercing a data type in Logstash

There are currently two ways to coerce Logstash to send numeric values: grok and mutate. You can also coerce types at the Elasticsearch level.

##### grok

Using grok to parse unstructured data into structured data can be a daunting task on its own. It can be downright confusing to tokenize numeric data into a field (let’s call it num) with the grok pattern %{NUMBER:num} only to find that Elasticsearch thinks num is a string field. Part of the confusion stems from the fact that grok treats the source data as a string since it is a regular expression engine. Because grok sees whatever is input as a string, without further information the output will also be a string. What we need is a way to tell grok and Logstash that the resulting value should be numeric.

The official documentation for grok explains it like this:

> Optionally you can add a data type conversion to your grok pattern. By default all semantics are saved as strings. If you wish to convert a semantic’s data type, for example change a string to an integer then suffix it with the target data type. For example %{NUMBER:num:int} which converts the num semantic from a string to an integer. Currently the only supported conversions are int and float.

So, if I add :int into my grok field definition, suddenly my value will be cast as an integer. Caveat: The NUMBER grok pattern will also detect numbers with decimal values. If you cast a number with a decimal as :int, it will truncate the decimal value leaving only the whole number portion.

In that case, the number can be cast as :float, meaning floating-point value.

##### mutate

Like grok, mutate also allows you to type your fields. The mutate filter currently allows you to convert a field into an integer, a float, or a string. Using our previous example of field num, the configuration would look something like this:

```
filter {
  mutate {
    convert => { "num" => "integer" }
  }
}
```

As with grok, converting a value with a decimal to type integer will truncate the decimal portion, leaving only the whole number.

Checking our work
If I were to check the mapping in Elasticsearch after typing the field num to an integer, I would find something unusual.

```
curl localhost:9200/Logstash-2014.10.07/_mapping?pretty
...
          "num" : {
            "type" : "long"
          }
...
```

It says that it’s type long. But I typed it as integer! What happened?

The answer is in the JSON. Logstash can only send JSON to Elasticsearch. If you recall our first example in this post, we sent a document with the field count with a value of 2048. Elasticsearch mapped that as type long also. We did the same in this example, but the field name was num. Unless you tell Elasticsearch what to expect, it can only make an educated guess how to interpret the JSON you send it.
