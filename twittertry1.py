import tweetstream
 
twitterUsername = "mithilesh_d27"
twitterPassword = "makemethylyre"
try:
    with tweetstream.TweetStream(twitterUsername, twitterPassword) as stream:
        for tweet in stream:
            try:
                print stream.count,"(",stream.rate,"tweets/sec). ",tweet['user']['screen_name'],':', tweet['text'].encode('utf-8')
                #print tweet #Use for raw output
            except:
                print "ERROR: Presumably missing field"
 
except tweetstream.ConnectionError, e:
    print "Disconnected from twitter. Reason:", e.reason
