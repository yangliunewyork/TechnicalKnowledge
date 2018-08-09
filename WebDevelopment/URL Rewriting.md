### What is "URL Rewriting"?

Most dynamic sites include variables in their URLs that tell the site what information to show the user. Typically, this gives URLs like the following, telling the relevant script on a site to load product number 7.

```
http://www.pets.com/show_a_product.php?product_id=7
```

The problems with this kind of URL structure are that the URL is not at all memorable. It's difficult to read out over the phone (you'd be surprised how many people pass URLs this way). Search engines and users alike get no useful information about the content of a page from that URL. You can't tell from that URL that that page allows you to buy a Norwegian Blue Parrot (lovely plumage). It's a fairly standard URL - the sort you'd get by default from most CMSes. Compare that to this URL:

```
http://www.pets.com/products/7/
```

Clearly a much cleaner and shorter URL. It's much easier to remember, and vastly easier to read out. That said, it doesn't exactly tellanyone what it refers to. But we can do more:

```
http://www.pets.com/parrots/norwegian-blue/
```

Now we're getting somewhere. You can tell from the URL, even when it's taken out of context, what you're likely to find on that page. Search engines can split that URL into words (hyphens in URLs are treated as spaces by search engines, whereas underscores are not), and they can use that information to better determine the content of the page. It's an easy URL to remember and to pass to another person.

Unfortunately, the last URL cannot be easily understood by a server without some work on our part. When a request is made for that URL, the server needs to work out how to process that URL so that it knows what to send back to the user. URL rewriting is the technique used to "translate" a URL like the last one into something the server can understand.

### Platforms and Tools

http://httpd.apache.org/docs/2.0/misc/rewriteguide.html

