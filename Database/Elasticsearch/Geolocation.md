# Geolocation

Gone are the days when we wander around a city with paper maps. Thanks to smartphones, we now know exactly where we are all the time, and we expect websites to use that information. I’m not interested in restaurants in Greater London—I want to know about restaurants within a 5-minute walk of my current location.

But geolocation is only one part of the puzzle. The beauty of Elasticsearch is that it allows you to combine geolocation with full-text search, structured search, and analytics.

For instance: show me restaurants that mention "vitello tonnato", are within a 5-minute walk, and are open at 11 p.m., and then rank them by a combination of user rating, distance, and price. Another example: show me a map of vacation rental properties available in August throughout the city, and calculate the average price per zone.

Elasticsearch offers two ways of representing geolocations: latitude-longitude points using the ```geo_point``` field type, and complex shapes defined in [GeoJSON](https://en.wikipedia.org/wiki/GeoJSON), using the ```geo_shape``` field type.

__Geo-points__ allow you to find points within a certain distance of another point, to calculate distances between two points for sorting or relevance scoring, or to aggregate into a grid to display on a map. __Geo-shapes__, on the other hand, are used purely for filtering. They can be used to decide whether two shapes overlap, or whether one shape completely contains other shapes.

# Geo Points

A geo-point is a single latitude/longitude point on the Earth’s surface. Geo-points can be used to calculate distance from a point, to determine whether a point falls within a bounding box, or in aggregations.

Geo-points cannot be automatically detected with dynamic mapping. Instead, geo_point fields should be mapped explicitly:

```
PUT /attractions
{
  "mappings": {
    "restaurant": {
      "properties": {
        "name": {
          "type": "string"
        },
        "location": {
          "type": "geo_point"
        }
      }
    }
  }
}
```

#### Lat/Lon Formats

With the location field defined as a geo_point, we can proceed to index documents containing latitude/longitude pairs, which can be formatted as strings, arrays, or objects:

```
PUT /attractions/restaurant/1
{
  "name":     "Chipotle Mexican Grill",
  "location": "40.715, -74.011" 
}

PUT /attractions/restaurant/2
{
  "name":     "Pala Pizza",
  "location": { 
    "lat":     40.722,
    "lon":    -73.989
  }
}

PUT /attractions/restaurant/3
{
  "name":     "Mini Munchies Pizza",
  "location": [ -73.983, 40.719 ] 
}
```

> Everybody gets caught at least once: string geo-points are "latitude,longitude", while array geo-points are [longitude,latitude]—the opposite order! Originally, both strings and arrays in Elasticsearch used latitude followed by longitude. However, it was decided early on to switch the order for arrays in order to conform with GeoJSON. The result is a bear trap that captures all unsuspecting users on their journey to full geolocation nirvana.

#### Filtering by Geo Point

Four geo-point filters can be used to include or exclude documents by geolocation:

geo_bounding_box : Find geo-points that fall within the specified rectangle.
geo_distance : Find geo-points within the specified distance of a central point.
geo_distance_range : Find geo-points within a specified minimum and maximum distance from a central point.
geo_polygon : Find geo-points that fall within the specified polygon. This filter is very expensive. If you find yourself wanting to use it, you should be looking at geo-shapes instead.


#### Geo Bounding Box Filter

This is by far the most efficient geo-filter because its calculation is very simple. You provide it with the top, bottom, left, and right coordinates of a rectangle, and all it does is compare the longitude with the left and right coordinates, and the latitude with the top and bottom coordinates:

```
GET /attractions/restaurant/_search
{
  "query": {
    "filtered": {
      "filter": {
        "geo_bounding_box": {
          "location": { 
            "top_left": {
              "lat":  40.8,
              "lon": -74.0
            },
            "bottom_right": {
              "lat":  40.7,
              "lon": -73.0
            }
          }
        }
      }
    }
  }
}
```

#### Geo Distance Filter

The geo_distance filter draws a circle around the specified location and finds all documents that have a geo-point within that circle:

```
GET /attractions/restaurant/_search
{
  "query": {
    "filtered": {
      "filter": {
        "geo_distance": {
          "distance": "1km", 
          "location": { 
            "lat":  40.715,
            "lon": -73.988
          }
        }
      }
    }
  }
}
```

#### Sorting by Distance

```
GET /attractions/restaurant/_search
{
  "query": {
    "filtered": {
      "filter": {
        "geo_bounding_box": {
          "type":       "indexed",
          "location": {
            "top_left": {
              "lat":  40.8,
              "lon": -74.0
            },
            "bottom_right": {
              "lat":  40.4,
              "lon": -73.0
            }
          }
        }
      }
    }
  },
  "sort": [
    {
      "_geo_distance": {
        "location": { 
          "lat":  40.715,
          "lon": -73.998
        },
        "order":         "asc",
        "unit":          "km", 
        "distance_type": "plane" 
      }
    }
  ]
}
```

# Geohashes

Geohashes are a way of encoding lat/lon points as strings. The original intention was to have a URL-friendly way of specifying geolocations, but geohashes have turned out to be a useful way of indexing geo-points and geo-shapes in databases.

Geohashes divide the world into a grid of 32 cells—4 rows and 8 columns—each represented by a letter or number. The g cell covers half of Greenland, all of Iceland, and most of Great Britain. Each cell can be further divided into another 32 cells, which can be divided into another 32 cells, and so on. The gc cell covers Ireland and England, gcp covers most of London and part of Southern England, and gcpuuz94k is the entrance to Buckingham Palace, accurate to about 5 meters.

![alt](https://i.stack.imgur.com/Nkp8B.jpg)

In other words, the longer the geohash string, the more accurate it is. If two geohashes share a prefix— and gcpuuz—then it implies that they are near each other. The longer the shared prefix, the closer they are.

That said, two locations that are right next to each other may have completely different geohashes. For instance, the Millenium Dome in London has geohash u10hbp, because it falls into the u cell, the next top-level cell to the east of the g cell.

Geo-points can index their associated geohashes automatically, but more important, they can also index all geohash prefixes. 

#### Mapping Geohashes

The first step is to decide just how much precision you need. Although you could index all geo-points with the default full 12 levels of precision, do you really need to be accurate to within a few centimeters? You can save yourself a lot of space in the index by reducing your precision requirements to something more realistic, such as 1km:

```
UT /attractions
{
  "mappings": {
    "restaurant": {
      "properties": {
        "name": {
          "type": "string"
        },
        "location": {
          "type":               "geo_point",
          "geohash_prefix":     true, 
          "geohash_precision":  "1km" 
        }
      }
    }
  }
}
```

#### Geohash Cell Query

The geohash_cell query simply translates a lat/lon location into a geohash with the specified precision and finds all locations that contain that geohash—a very efficient query indeed.

```
GET /attractions/restaurant/_search
{
  "query": {
    "constant_score": {
      "filter": {
        "geohash_cell": {
          "location": {
            "lat":  40.718,
            "lon": -73.983
          },
          "precision": "2km" 
        }
      }
    }
  }
}
```

This query translates the lat/lon point into a geohash of the appropriate length—in this example dr5rsk—and looks for all locations that contain that exact term.

However, the query as written in the preceding example may not return all restaurants within 5km of the specified point. Remember that a geohash is just a rectangle, and the point may fall anywhere within that rectangle. If the point happens to fall near the edge of a geohash cell, the filter may well exclude any restaurants in the adjacent cell.

To fix that, we can tell the query to include the neigboring cells, by setting neighbors to true:

```
GET /attractions/restaurant/_search
{
  "query": {
    "constant_score": {
      "filter": {
        "geohash_cell": {
          "location": {
            "lat":  40.718,
            "lon": -73.983
          },
          "neighbors": true, 
          "precision": "2km"
        }
      }
    }
  }
}
```

Clearly, looking for a geohash with precision 2km plus all the neighboring cells results in quite a large search area. This query is not built for accuracy, but it is very efficient and can be used as a prefiltering step before applying a more accurate geo-filter.

# Geo Aggregations

Although filtering or scoring results by geolocation is useful, it is often more useful to be able to present information to the user on a map. A search may return way too many results to be able to display each geo-point individually, but geo-aggregations can be used to cluster geo-points into more manageable buckets.

Three aggregations work with fields of type geo_point:

* geo_distance : Groups documents into concentric circles around a central point.
* geohash_grid : Groups documents by geohash cell, for display on a map.
* geo_bounds : Returns the lat/lon coordinates of a bounding box that would encompass all of the geo-points. This is useful for choosing the correct zoom level when displaying a map.

