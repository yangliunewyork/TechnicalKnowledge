https://en.wikipedia.org/wiki/Internationalization_and_localization

In computing, internationalization and localization are means of adapting computer software to different languages, regional differences and technical requirements of a target locale.[1] Internationalization is the process of designing a software application so that it can be adapted to various languages and regions without engineering changes. Localization is the process of adapting internationalized software for a specific region or language by translating text and adding locale-specific components. Localization (which is potentially performed multiple times, for different locales) uses the infrastructure or flexibility provided by internationalization (which is ideally performed only once, or as an integral part of ongoing development).

> The terms are frequently abbreviated to the numeronyms i18n (where 18 stands for the number of letters between the first i and the last n in the word internationalization, a usage coined at Digital Equipment Corporation in the 1970s or 1980s)[3][4] and L10n for localization, due to the length of the words.


### Localization vs. internationalization

Localization and internationalization are two terms that are commonly used interchangeably, but they are very distinct. Internationalization, also referred to as I18N, is the design and development of a product that is enabled for target audiences that vary in culture, region, or language. Internationalization is a coding architecture that enables the same code to be used for multiple countries or languages, while localization needs to be done for every country or language.

The ease of localization is very dependent on internationalization or how localizable the product is.  At the technical level, being internationally-aware means writing code that is designed to be easily internationalized in all ways (strings, dates, currencies, etc.) and easily deployable to any locale.  Failure to internationalize leads to code rework and long delays in deployment to additional locales.

### Best practices for internationalization

Below are some guidelines for ensuring that code is localizable:

* Separate localizable resources such as text strings and images from the code base so that they can be independently localized and plugged back into the final product without requiring code changes.
* Screen and print layout code should be flexible. Frames and buttons, for example, should be designed so that they will expand or shrink to accommodate localized string lengths; there can be up to 40% text expansion for languages such as German.
* Word order should be flexible so that language-specific grammatical structures are supported within the code.
* Code design and implementation should allow for the use of local currency format, date format, calendar, and payment methods. Text input and font selection should be enabled and verified for all supported languages and scripts. By enabling font selection, users can select the most appropriate font for their language.
* Providing suggestions, such as search terms, should be tailored for each language and market.
* Sensible default values should be used in each market. Consider allowing users to customize their choices where appropriate.


Translation is the process of converting one language to another language, like English to French. Translation is a major part of the localization (L10N) process, which is the adaptation of a product, application, or document content to meet the language, cultural, and other requirements of a specific target audience. The goal of localization is to make users feel as if the product were developed specifically for them. 

