https://aws.amazon.com/lambda/  
https://www.networkworld.com/article/3053111/cloud-computing/what-is-amazon-cloud-s-lambda-and-why-is-it-a-big-deal.html  

AWS Lambda is an event-driven, serverless computing platform provided by Amazon as a part of the Amazon Web Services. It is a computing service that runs code in response to events and automatically manages the computing resources required by that code. It was introduced in November 2014.

The purpose of Lambda, as compared to AWS EC2, is to simplify building smaller, on-demand applications that are responsive to events and new information. AWS targets starting a Lambda instance within milliseconds of an event. Node.js, Python, Java, Go[2] and C# through .NET Core are all officially supported as of 2016, and other languages can be supported via call-outs. However, some runtimes, such as the Java virtual machine, may be slower than others to start.

AWS Lambda supports securely running native Linux executables via calling out from a supported runtime such as Node.js.[3] For example, Haskell code can be run on Lambda.

AWS Lambda was designed for use cases such as image or objects uploads to Amazon S3, updates to DynamoDB tables, responding to website clicks or reacting to sensor readings from an IoT connected device. AWS Lambda can also be used to automatically provision back-end services triggered by custom HTTP requests, and "spin down" such services when not in use, to save resources. These custom HTTP requests are configured in AWS API Gateway, which can also handle authentication and authorization in conjunction with AWS Cognito.

Unlike Amazon EC2, which is priced by the hour but metered by the second, AWS Lambda is metered in increments of 100 milliseconds. Usage amounts below a documented threshold fall within the AWS Lambda free tier - which does not expire 12 months after account signup, unlike the free tier for some AWS services.

### What is Amazon cloud’s Lambda and why is it a big deal? 

“AWS Lambda lets you run code without provisioning or managing servers,” AWS states on the Lambda product page. You can think of Lambda as an event-driven computing platform; Lambda runs when triggered by an event and executes code that’s been loaded into the system.

For example, a simple use case would be that every time an image is uploaded into Amazon Simple Storage Service (S3), a Lambda function could automatically resize the image. The Seattle Times uses this to automatically resize images for mobile, tablet and desktop devices. The event that triggers the Lambda function is the file being uploaded to S3. Lambda then executes the function of resizing the image.

One key to Lambda is that customers only pay for the service when functions are executed. So, the Seattle Times only pays AWS when an image has been resized. 

Wood said Lambda could be helpful in analytics too. When an online order is placed on Zillow, an entry is made into Amazon DynamoDB NoSQL database. That entry into the database triggers a Lambda function to load the order information into Amazon Redshift, the data warehouse. Analytics programs can be run ontop of data stored in Redshift.

This, Wood says, is ushering in a new era of application architecture. “There’s a particular category of usage where the developer wants to focus primarily on adding functionality to their application, they don’t want to worry about scaling up and down (infrastructure), and they want costs that run in line with usage of their application, not the utilization of their infrastructure,” Wood told me. “Lambda provides a really good answer for developers looking for that sort of focus.”

Amazon’s competitors have their own versions of Lambda. Google has Functions; IBM has open sourced a platform named OpenWhisk and Microsoft recently released Azure Functions. It’s a trendy new platform in the cloud, but Amazon is credited with being the first to market when it introduced Lambda at its re:Invent conference in 2014.

Amazon uses Lambda internally. Lambda is the compute platform for AWS’s Internet of Things service and the Amazon Echo. Amazon CloudWatch events allow users to automatically trigger a patch of an Amazon Elastic Compute Cloud (EC2) virtual machine instance if it fails.

But perhaps what is most interesting about Lambda is that it could threaten one of Amazon’s most popular services: EC2, it’s virtual machine service. Developers can build apps that run entirely on Lambda functions instead of spinning up EC2 VMs. Amazon may be out-innovating itself with Lambda.

