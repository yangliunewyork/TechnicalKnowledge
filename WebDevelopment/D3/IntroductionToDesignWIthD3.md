## Technology Fundamentals

### Web
Web servers are Internet-connected computers running server software, so called be‐ cause they serve web documents as requested. Servers are typically always on and always connected, but web developers often also run local servers, meaning they run on the same computer that you’re working on. Local means here; remote means somewhere else, on any computer but the one right in front of you.

Complete URLs consist of four parts:
* An indication of the communication protocol, such as HTTP or HTTPS
* The domain name of the resource, such as calmingmanatee.com
* The port number, indicating over which port the connection to the server should be attempted
* Any additional locating information, such as the path of the requested file, or any query parameters

HTTP stands for Hypertext Transfer Protocol, and it’s the most common protocol for transferring web content from server to client. The “S” on the end of HTTPS stands for Secure. HTTPS connections are used whenever information should be encrypted in transit, such as for online banking or e-commerce.

### HTML
Hypertext Markup Language is used to structure content for web browsers. HTML is stored in plain text files with the .html suffix.HTML is a tool for specifying semantic structure, or attaching hierarchy, relationships, and meaning to content. (HTML doesn’t address the visual representation of a document’s structure—that’s CSS’ job.) .

There are hundreds of different HTML elements. Here are some of the most common.
* <!DOCTYPE html> : The standard document type declaration. Must be the first thing in the document.
* html : Surrounds all HTML content in a document.
* head : The document head contains all metadata about the document, such as its title and any references to external stylesheets and scripts.
* title : The title of the document. Browsers typically display this at the top of the browser window and use this title when bookmarking a page.
* body : Everything not in the head should go in the body. This is the primary visible content of the page.

Classes and IDs are extremely useful attributes, as they can be referenced later to identify specific pieces of content. Your CSS and JavaScript code will rely heavily on classes and IDs to identify elements.

```
<p class="awesome">Awe-inspiring paragraph</p>
<div id="visualization"></div>
```

### DOM
The term __Document Object Model__ refers to the hierarchical structure of HTML. Each pair of bracketed tags (or, in some cases, a single tag) is an element, and we refer to elements’ relative relationships to each other in human terms: parent, child, sibling, ancestor, and descendant. 


### Rendering and the Box Model
Rendering is the process by which browsers, after parsing the HTML and generating the DOM, apply visual rules to the DOM contents and draw those pixels to the screen.

__The most important thing to keep in mind when considering how browsers render content is this: to a browser, everything is a box.__

Paragraphs, divs, spans—all are boxes in the sense that they are two-dimensional rectangles, with properties that any rectangle can have, such as width, height, and positions in space. Even if something looks curved or irregularly shaped, rest assured, to the browser, it is merely another rectangular box.

By default, block-level elements expand to fill their container elements and force any subsequent sibling elements further down the page. Inline elements do not expand to fill extra space, and happily exist side by side, next to their fellow inline neighbors.

### CSS
Cascading Style Sheets are used to style the visual presentation of DOM elements.
CSS styles consist of selectors and properties. Selectors are followed by properties, grou‐ ped in curly brackets. A property and its value are separated by a colon, and the line is terminated with a semicolon, like the following:
```
selector {
  property: value;
  property: value;
  property: value;
}
```

Selectors identify specific elements to which styles will be applied. There are several different kinds of selectors. We’ll use only the simplest ones here.

##### Type selectors
These are the simplest. They match DOM elements with the same name:
```
h1 /* Selects all level 1 headings */ 
p /* Selects all paragraphs */ 
strong /* Selects all strong elements */ 
em /* Selects all em elements */ 
div /* Selects all divs */
```

##### Descendant selectors
These match elements that are contained by (or “descended from”) another element. We will rely heavily on descendant selectors to apply styles:
```
h1 em /* Selects em elements contained in an h1 */ 
div p /* Selects p elements contained in a div */
```

##### Class selectors
These match elements of any type that have been assigned a specific class. Class names are preceded with a period, as shown here:
```
.caption /* Selects elements with class "caption" */ 
.label /* Selects elements with class "label" */ 
.axis /* Selects elements with class "axis" */
```
Because elements can have more than one class, you can target elements with multiple classes by stringing the classes together, as in the following:
```
.bar.highlight /* Could target highlighted bars */ 
.axis.x /* Could target an x-axis */ 
.axis.y /* Could target a y-axis */
```
.axis could be used to apply styles to both axes, for example, whereas .axis.x would apply only to the x-axis.

##### ID selectors
These match the single element with a given ID. (Remember, IDs can be used only once each in the DOM.) IDs are preceded with a hash mark.
````
#header /* Selects element with ID "header" */ 
#nav /* Selects element with ID "nav" */ 
#export /* Selects element with ID "export" */
```

### Inheritance, Cascading, and Specificity
Many style properties are inherited by an element’s descendants unless otherwise specified.Inheritance is a great feature of CSS, as children adopt the styles of their parents. 

Finally, an answer to the most pressing question of the day: why are they called Cas‐ cading Style Sheets? It’s because selector matches cascade from the top down. When more than one selector applies to an element, the later rule generally overrides the earlier one. 

```
p{
color: blue;
}

p.highlight { 
color: black;
background-color: yellow; 
}
```

Later rules generally override earlier ones, but not always. The true logic has to do with the specificity of each selector. The p.highlight selector would override the p rule even if it were listed first, simply because it is a more specific selector. If two selectors have the same specificity, then the later one will be applied.

This is one of the main causes of confusion with CSS. The rules for calculating specificity are inscrutable, and I won’t cover them here. To save yourself headaches later, keep your selectors clear and easy to read. Start with general selectors on top, and work your way down to more specific ones, and you’ll be all right.

### JavaScript
JavaScript is the scripting language that can make pages dynamic by manipulating the DOM after a page has already loaded in the browser. JavaScript is a loosely typed language, meaning you don’t have to specify what type of information will be stored in a variable in advance. 

JavaScript, however, automatically types a variable based on what kind of information you assign to it. (Note that '' or "" indicate string values.)

In programming, the concept of variable scope helps us identify which variables are accessible in which contexts. Generally, it is a bad idea to have every value accessible from everywhere else because you’d end up with so many conflicts and accidental value changes that you would just go crazy.

Many languages use block-level scope, in which variables exist only within the current “block” of code, usually indicated by curly braces. With block-level scope, our i would exist only within the context of the for loop, for example, so any attempts to read the value of i or change i outside of the loop would fail. This is nice because you could establish other variables from within your loop and know that they wouldn’t conflict with variables that exist elsewhere.

In JavaScript, however, variables are scoped at the function level, meaning they are accessible anywhere within the function (not block) in which they reside.This is primarily something to be aware of if you’re used to other languages. Bottom line: You can keep values contained by wrapping them within functions.

window is the topmost object in the browser’s hierarchy of JavaScript elements, and all of these objects and values you see beneath window exist at the global level. What this means is that every time you declare a new variable, you are adding a new value to window. Or, as righteous JavaScript coders like to say, you are polluting the global namespace. 

There are two easy workarounds (and, to clarify, you probably don’t have to worry about this until later):
* Declare variables only within other functions. This is not usually feasible, but the function-level scope will prevent local variables from conflicting with others.
* Declare a single global object, and attach all of your would-be global variables to that object. 

For example:
```
var Vis = {}; //Declare empty global object Vis.zebras = "still pretty amazing"; 
Vis.monkeys = "too funny LOL";
Vis.fish = "you know, not bad";
```
All of your weird animal-related variables are no longer polluting the global namespace, but instead they all exist as values stored within your single, global object, Vis. Of course, Vis could be named whatever you like, but Menagerie is harder to type. Regardless, the only naming conflict you’ll have with other scripts is if one of them also wants to have a global object with the same name (Vis), which is far less likely.

### SVG
D3 is most useful when used to generate and manipulate visuals as Scalable Vector Graphics (SVG). Drawing with divs and other native HTML elements is possible, but a bit clunky and subject to the usual inconsistencies across different browsers. Using SVG is more reliable, visually consistent, and faster.

SVG is a text-based image format. Each SVG image is defined using markup code similar to HTML, and SVG code can be included directly within any HTML document, or inserted dynamically into the DOM.  Before you can draw anything, you must create an SVG element. Think of the SVG element as a canvas on which your visuals are rendered. (In that respect, SVG is con‐ ceptually similar to HTML’s canvas element.) There are a number of visual elements that you can include between those svg tags, including rect, circle, ellipse, line, text, and path, etc.

SVG’s default style is a black fill with no stroke. If you want anything else, you’ll have to apply styles to your elements. Common SVG properties are as follows:
* fill : A color value. Just as with CSS, colors can be specified as named colors, hex values, or RGB or RGBA values.
* stroke : A color value.
* stroke-width : A numeric measurement (typically in pixels).
* opacity : A numeric value between 0.0 (completely transparent) and 1.0 (completely opaque).
* text :  you can also use these properties, which work just like in CSS: font-family and font-size

## Data
Typically, when using D3 to generate new DOM elements, the new elements will be circles, rectangles, or other visual forms that represent your data.

D3 smartly employs a technique called chain syntax, which you might recognize from jQuery. By “chaining” methods together with periods, you can perform several actions in a single line of code. It can be fast and easy, but it’s important to understand how it works, to save yourself hours of debugging headaches later.

Many, but not all, D3 methods return a selection (actually, a reference to a selection), which enables this handy technique of method chaining. Typically, a method returns a reference to the element that it just acted on, but not always.
So remember this: when chaining methods, order matters. The output type of one method has to match the input type expected by the next method in the chain. If adjacent inputs and outputs are mismatched, the hand-off will function more like a dropped baton in a middle-school relay race.

Data visualization is a process of mapping data to visuals. Data in, visual properties out. Maybe bigger numbers make taller bars, or special categories trigger brighter colors. The mapping rules are up to you.

With D3, we bind our data input values to elements in the DOM. Binding is like “at‐ taching” or associating data to specific elements, so that later you can reference those values to apply mapping rules. Without the binding step, we have a bunch of data-less, unmappable DOM elements. No one wants that.

```
 d3.select("body").selectAll("p")
        .data(dataset)
        .enter()
        .append("p")
        .text("New paragraph!");
 ```
 
 Here’s what’s happening:

d3.select("body") : Finds the body in the DOM and hands off a reference to the next step in the chain.
.selectAll("p") : Selects all paragraphs in the DOM. Because none exist yet, this returns an empty selection. Think of this empty selection as representing the paragraphs that will soon exist.
.data(dataset) : Counts and parses our data values. There are five values in our array called data set, so everything past this point is executed five times, once for each value.
.enter() : To create new, data-bound elements, you must use enter(). This method looks at the current DOM selection, and then at the data being handed to it. If there are more data values than corresponding DOM elements, then enter() creates a new placeholder element on which you can work your magic. It then hands off a reference to this new placeholder to the next step in the chain.
.append("p") : Takes the empty placeholder selection created by enter() and appends a p element into the DOM. Hooray! Then it hands off a reference to the element it just created to the next step in the chain.
.text("New paragraph!") : Takes the reference to the newly created p and inserts a text value.


## Drawing with Data

