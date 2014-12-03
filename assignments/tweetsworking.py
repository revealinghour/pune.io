import os
import sys
import tweepy

os.chdir('/home/mithilesh/Desktop/Twitter')

consumer_key = 'consumer_key'
consumer_secret = 'consumer_secret'
access_token = 'access_token'
access_secret = 'access_secret'

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_secret)
api = tweepy.API(auth)

# count is used to give an approximation of how many tweets I'm pulling at a given time.

count = [10]
f = open('tweet1.txt', 'a')

class StreamListener(tweepy.StreamListener):
    def on_status(self, status):
        print 'Running...'
        info = status.text, status.created_at, status.id
        f.write(str(info))
        for i in info:
          count.append(1)

    def on_error(self, status_code):
        print >> sys.stderr, "Encountered error with status code: ", status_code

    def on_timeout(self):
        print >> sys.stderr, "Timeout..."
        return True

sapi = tweepy.streaming.Stream(auth, StreamListener())
sapi.filter(track=["pune"])
