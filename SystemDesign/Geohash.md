__Geohash__ is a public domain geocoding system invented by Gustavo Niemeyer, which encodes a geographic location into a short string of letters and digits. It is a hierarchical spatial data structure which subdivides space into buckets of grid shape, which is one of the many applications of what is known as a __Z-order curve__, and generally __space-filling curves__.

Geohashes offer properties like arbitrary precision and the possibility of gradually removing characters from the end of the code to reduce its size (and gradually lose precision). As a consequence of the gradual precision degradation, nearby places will often (but not always) present similar prefixes. The longer a shared prefix is, the closer the two places are.

A geohash is an encoded character string that is computed from geographic coordinates. For example the approximate latitude and longitude of The National Center For Ecological Analysis and Synthesis is 34.419279, -119.698472 from which the geohash of 9q4gu1y4z can be derived. __The geohash algorithm is bidirectional, so geographic coordinates can be encoded into geohashes and geohashes can be decoded to obtain coordinates.__

__Geohashes have the property that characters can be incrementally removed from the right side of the geohash to represent a geographic location less precisely. A geohash is an approximation of a point, where each length of the geohash corresponds to a rectangle (a geohash tile) that is an approximation of the original encoded geographic coordinate.__

This feature of geohashes can be useful for searching and plotting at different resolutions.

Table 1 shows the relationship between geohash length and the size of the rectangle represented by that geohash at the equator.

```
Length	Tile Size
1	5,009.4km x 4,992.6km
2	1,252.3km x 624.1km
3	156.5km x 156km
4	39.1km x 19.5km
5	4.9km x 4.9km
6	1.2km x 609.4m
7	152.9m x 152.4m
8	38.2m x 19m
9	4.8m x 4.8m
10	1.2m x 59.5cm
11	14.9cm x 14.9cm
12	3.7cm x 1.9cm
```

Table 2 shows the relationship between a geohash and the resulting latitude and longitude decoded from the different length geohashes. As characters are removed from the original geohash ‘9q4gu1y4z’ the bounding rectangle and the accuracy of the decoded geohash becomes less precise. The decoded geohash corresponds to the centroid of the bounding rectangle.

```
Geohash	Tile         Center lat, long	                 Tile minlat, minlong, maxlat, maxLong
9	                    22.5,-112.5	                       0, -135,  45, -90
9q	                  36.5625, -118.125	                 33.75, -123.75, 39.375, -112.5
9q4	                  34.45312,  -120.23437	             33.75, -120.9375, 35.15625, -119.53125
9q4g	                34.36523, -119.70703	             34.27734, -119.88281, 34.45312, -119.53125
9q4gu	                34.43115, -119.68505	             34.40917, -119.70703, 34.45312, -119.66308
9q4gu1	              34.41741, -119.70153	             34.41467, -119.70703, 34.42016, -119.69604
9q4gu1y	              34.41947, -119.69810	             34.41879, -119.69879, 34.42016, -119.69741
9q4gu1y4	        34.41922, -119.69861	          34.41913, -119.69879, 34.41930, -119.69844
9q4gu1y4z	        34.41928, -119.69846	          34.41926, -119.69849, 34.41930, -119.69844

```

Geohashes comprise a nested spatial indexing system with each level of geohashes tile containing 32 tiles of the next smaller tile size. The level one geohashes (length=1) divide the earth into 32 tiles. Each of these 32 tiles is then subdivided into 32 level 2 tiles and so on.

Geohashes also have the property that all smaller tiles within the enclosing geohash tile begin with the same leading characters, therefor for the level 1 tile ‘9’, all level 2 sub-tiles begin with ‘9’: ‘90’, ‘91’, ‘93’,..., ‘9z’.

For example the level 3 geohash tile that encloses much of Santa Barbara County is ‘9q4’. Also contained in this bounding rectangle is the city center of Santa Maria (geohash 9q4qg7j2hmdz), Goleta (geohash 9q4gckb5jxu7) and Santa Barbara (geohash 9q4gu4n7y5b7) all of which begin with the characters ‘9q4’ and fall within the ‘9q4’ geohash rectangle. This property is very useful for searching and sorting datastores that contain geohashes.

# Web site geohash.org

In February 2008, together with the announcement of the system, the inventor launched the website http://geohash.org/, which allows users to convert geographic coordinates to short URLs which uniquely identify positions on the Earth, so that referencing them in emails, forums, and websites is more convenient.

To obtain the Geohash, the user provides an address to be __geocoded__, or latitude and longitude coordinates, in a single input box (most commonly used formats for latitude and longitude pairs are accepted), and performs the request.

Besides showing the latitude and longitude corresponding to the given Geohash, users who navigate to a Geohash at geohash.org are also presented with an embedded map, and may download a GPX file, or transfer the waypoint directly to certain GPS receivers. Links are also provided to external sites that may provide further details around the specified location.

For example, the coordinate pair ```57.64911,10.40744``` (near the tip of the peninsula of Jutland, Denmark) produces a slightly shorter hash of ```u4pruydqqvj```.

# Uses

The main usages of Geohashes are:

* As a unique identifier.
* To represent point data, e.g. in databases.

Geohashes have also been proposed to be used for __geotagging__.

When used in a database, the structure of geohashed data has two advantages. First, data indexed by geohash will have all points for a given rectangular area in contiguous slices (the number of slices depends on the precision required and the presence of geohash "fault lines"). This is especially useful in database systems where queries on a single index are much easier or faster than multiple-index queries. Second, this index structure can be used for a quick-and-dirty proximity search: the closest points are often among the closest geohashes.

# Intro with example

We have a location on the world map (see the red dot) and we want to represent this point as a single value Geohash.

![alt](http://commondatastorage.googleapis.com/philwhln/blog/images/geohash/geohash-0.png)

First we divide the world into two halves with a vertical line and give each half a binary value of either 0 or 1. Our point on the map is in the “0″ half.

At this point we could be very unhelpful and say that the Geohash is “0″. This is lowest resolution Geohash. Obviously this is not much use if you are trying to locate a party on Saturday night and your friend tells you that the party is on the west half of planet. If he does, then take the hint and stay home.

Let’s improve the resolution of our Geohash…

Next we sub-divide our “0″ half of planet into two halves with a horizontal line and assign each half a “0″ or “1″.


![alt](http://commondatastorage.googleapis.com/philwhln/blog/images/geohash/geohash-00.png)

We can see our red dot is located in the “0″ half, so we have a higher resolution Geohash of “00″ (“0″ from the first division, and “0″ from the sub-division).

Great! Your chances of attending the party have doubled, but we will need to raise the resolution further to pin-point more accurately.

![alt](http://commondatastorage.googleapis.com/philwhln/blog/images/geohash/geohash-001.png)

Another sub-division gives us a location of “001″ (“0″ from the first division, and “0″ from the first sub-division and “1″ from this second sub-division).

I hope that you are getting the idea by now.

Note that each sub-division switches between dividing vertically and horizontally, dividing longitude and latitude alternately. This interweaves the longitude and latitude information to give a single value.

We can keep sub-dividing the space until we get to street-level or beyond. At that point our Geohash will be a bit longer and will look something like this…

```
0010110101011100011000110001101111000111
```

This binary can be represented as alphanumeric characters (32 bit encoded). Each 5 bits is converted to one character:

```
00101  10101  01110  00110  00110  00110  11110  00111
```

Which comes out as

```
 5      p      f      6      6      6      y      7
```

So our Geohash for the party on Saturday night is “5pf666y7″.

That’s great, but how does that help us?

### Why Use A GeoHash?

##### Single Simple String Representation

A Geohash is fairly short and concise and does not have to be a precise location. It looks similar to a URL shortener string, such as http://bit.ly/12C5kv, and can be passed around on social networks such as Twitter.

##### Grouping Of Points

This is my favorite part about the Geohash system. Geohashs can easily to grouped. No advanced algorithms needed.

It is as simple as saying, which other points have a Geohash that starts with the prefix “5pf66″?. The longer the prefix the higher resolution we can zoom to.

##### Zooming And Aggregation

If we want to zoom in and out on a map and show a summary of how many points there are on grid square, then we can use a Geohash prefix length that is relative to the zoom resolution

In this example we use a prefix of 2 characters, which will give us the world map divided into 64 (2×32) grid squares, and a count of the number of points found in each one.

```sql
SELECT SUBSTR(geohash, 0, 2), COUNT(*) FROM locations GROUP BY SUBSTR(geohash, 0, 2);
```

```
"aa", 67
"ab", 456
"ac", 128
"ad", 994
"ae", 12
...
"zx", 0
"zy", 8
"zz", 5
```

A simple index on the geohash column of the above locations table allows us to focus any queries on specific areas on the map.

#### Caching At Scale

A question I often ask when looking at using technologies, is “how does it scale“? Can the data be partitioned? Can we cache the results? The Geohash system provides this through simply prefixes.

You can be sure that Google heavily caches all the grid squares on Google Maps at the various resolutions they provide.

All point data that relates to a specific grid square at a specific resolution can be cached by using that grid square’s geohash value. Using this single value, rather than 4 non-discrete co-ordinates values (top, left, bottom, right), we can use a key-value datastore (HBase, MongoDB, Cassandra, Memcached, CouchBase, Memcached.. ) to store and quickly retrieve all information on that grid-square.

From our above example, if we were to update the party location details at Geohash location “5pf666y7″, we could then quickly update the aggregate information at the lower resolutions “5pf666y”, “5pf666″, “5pf66″, “5pf6″, “5pf”, “5p” and “5″. By doing this pre-computation we could have that data ready to be served up as-is from our key-value store, as the users of our website zoom in-and-out and move around the map.

#### Finding Nearest Points

An index of geohash values will store the geohashs in alphanumeric order. This means nearest points are the closest strings. This makes the 2D problem a much simplier 1D problem (see “The Gotcha!”)

```
22rt841  <-- Far way party
5pf666y  <-- Somebody else's party nearby
5pf666y  <-- Our party
5pf666y  <-- Another nearby party
5r84ew3  <-- Not so close party
```

#### The Gotcha!

You get extra points if you have already spotted the problem with finding nearest neighbours.

The nearest point can have wildly different Geohash value, if the location is close to a grid-square boundary. This is similar to two nearby houses that reside on opposite sides of an international border (eg. Canada and USA). There will be no commonality in the addresses of these two houses.

![alt](http://commondatastorage.googleapis.com/philwhln/blog/images/geohash/geohash-gotcha.png)

In this example above you can see that these 2 locations (green dot and red dot) are pretty close, but they on opposite sides of a boundary. Immediately they will start with opposite binary values. Many subsequent horizontal divisions will see the green dot on the far right (“1″) of the division and the red dot on the far left (“0″). There will be very little correlation in the geohash values of these two neighbouring dots.

#### The Gotcha Solution

Fear not, the smart people at the institute of super smart people have a solution for you. There is an algorithm for calculating the geohash values of the 8 surrounding grid-squares of a given grid square, which widens our search net in all directions, allowing us to see nearby points that reside on the other side of a grid’s boundary.



