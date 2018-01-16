This is a quick tutorial to have func with Logstash and Filebeat.

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

### Configuring Logstash for Filebeat Inputedit

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
