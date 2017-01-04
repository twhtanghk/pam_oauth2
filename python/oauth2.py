import os
import requests
import hashlib
import json

'''
  authenticate user and return oauth2 response
'''
def login(user):
  data = { 'grant_type': 'password', 'username': user['id'], 'password': user['secret'], 'scope': os.environ['SCOPE'] } 
  return requests.post(os.environ['TOKENURL'], auth=(os.environ['CLIENT_ID'], os.environ['CLIENT_SECRET']), data=data)

'''
  authenticate user and return token
'''
def token(user):
  res = json.loads(login(user).text)
  return res['access_token']

'''
  authenticate user and return if athenticated
'''
def isauth(user):
  return login(user).status_code == 200

'''
user = 'user1'
'''
def isuser(user):
  r = requests.get(os.environ['USERURL'].format(user))
  return userJson(json.loads(r.text)) if r.status_code == 200 else None

'''
return json resprentation of input user
'''
def userJson(user):
  name = user['username']
  uid = int(hashlib.sha1(user['url'].encode('utf-8')).hexdigest(), 16) % (10 ** 8)
  gid = 10000
  home = "/home/{0}".format(name)
  shell = '/bin/sh'
  return {'name': name, 'uid': uid, 'gid': gid, 'home': home, 'shell': shell}

'''
return list of users
'''
def users():
  users = []
  res = {'next': os.environ['USERLISTURL']}
  while res['next']:
    r = requests.get(res['next'])
    res = json.loads(r.text)
    for user in res['results']:
      users.append(userJson(user))
  return users
