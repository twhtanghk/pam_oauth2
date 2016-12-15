import os
import requests
import hashlib
import json
import pydash
from requests.auth import HTTPBasicAuth

cfg = {
  'tokenurl': os.environ['TOKENURL'],
  'userurl': os.environ['USERURL'],
  'userlisturl': os.environ['USERLISTURL'],
  'client': {
    'id': os.environ['CLIENT_ID'],
    'secret': os.environ['CLIENT_SECRET']
  },
  'user': {
    'id': os.environ['USER_ID'],
    'secret': os.environ['USER_SECRET']
  },
  'scope': 'User' if 'SCOPE' not in os.environ else os.environ['SCOPE']
}

'''
  authenticate cfg.user and return oauth2 response
'''
def login(user):
  data = { 'grant_type': 'password', 'username': user['id'], 'password': user['secret'], 'scope': cfg['scope'] } 
  return requests.post(cfg['tokenurl'], auth=(cfg['client']['id'], cfg['client']['secret']), data=data)

'''
  authenticate cfg.user and return token
'''
def token(user):
  res = json.loads(login(user).text)
  return res['access_token']

'''
  authenticate cfg.user and return if athenticated
'''
def isauth(user):
  return login(user).status_code == 200

'''
user = 'user1'
'''
def isuser(user):
  ret = pydash.filter_(users(), {'name': user})
  return pydash.first(ret)

'''
return json resprentation of input user
'''
def userJson(user):
  name = user['username']
  uid = int(hashlib.sha1(user['url']).hexdigest(), 16) % (10 ** 8)
  gid = 10000
  home = "/home/{0}".format(name)
  shell = '/bin/sh'
  return {'name': name, 'uid': uid, 'gid': gid, 'home': home, 'shell': shell}
'''
return list of users
'''
def users():
  ptoken = token(cfg['user']) 
  users = []
  res = {'next': cfg['userlisturl']}
  while res['next']:
    r = requests.get(res['next'], headers={'Authorization': "Bearer {0}".format(ptoken)})
    res = json.loads(r.text)
    for user in res['results']:
      users.append(userJson(user))
  return users
