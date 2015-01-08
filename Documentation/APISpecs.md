##Input Specification
###URL string
This string is used for logging of data of a stream with 2 fields namely field1 and field2. If you have more fields, the number of fields in the string increases.

     http://data.pune.io/input/public_key&private_key="PRIVATEKEY"&field1="value"&field2="value"

###URL string with response type 
If you require a specific format of responses from the server and if your client is capable of parsing a json or jsonp response then use the following string.

    http://data.pune.io/input/public_key&private_key="PRIVATEKEY"&field1="value"&field2="value".json
    http://data.pune.io/input/public_key&private_key="PRIVATEKEY"&field1="value"&field2="value".jsonp  

##Output Specification
###URL String
    http://data.pune.io/output/public_key.format

**_The url can also contain query string with which different features can be used._**

###Location
A location query parameter can be used to specify the location from which the data has to be accessed. The location can be given in format of text. For example if you want data specific to the location of Viman Nagar, then use the following url string. 

    http://data.pune.io/output/public_key.format?location="vimanagar"

###Time
A time query parameter can be added along with other query parameters to download data sensitive to time. Another query parameter has to be added along with it to specify whether you require data after the specified time or before the specified time. The below url if for before the time. If you require data after time simply change the value of after to 1.

    http://data.pune.io/output/public_key.format?time="required time"&after="0"

###Separate Data
You can also download only a specific field of your data stream. If your data stream has more than one field then you can specifically download a field by using the name of the field as a query parameter. The following is an url example to download the field "temp" of a data stream.

    http://data.pune.io/output/public_key.format?temp


###Device
If you require to download the data uploaded by a specific device in a particular area, then you can also use the device query parameter to do so. This query parameter can be used independently or in combination with the location parameter.

    http://data.pune.io/output/public_key.format?location="vimannagar"&device="deviceid"

###Alldata
If you require to download all the data in the stream irrespective of any filters, then you just have to use a query string of alldata. By using this query parameter, you will be downloading the data uploaded by every device in the area. An example to download all the data.

    http://data.pune.io/output/public_key.format?alldata