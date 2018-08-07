# A C++ client for Redis

- It uses anet from Redis itself
- It has been tested with g++ on Linux
- Sharding (consistent hashing with support for user-specified algorithm)

## Notes on consistent hashing / sharding

The redis-cpp supports nearly all commands in multi-server mode.
As the sharding is based on the key name by consistent hashing, multi key commands must call more then one server
and do some local aggregation. This means that you loose the atomicity which is normally guaranteed by redis.
When using read-only commands like MGET this might only be a small problem in your use-cases. But this can lead to hard to
trace race-conditions when using writing commands like MSETNX, where the command must be undone on the first servers when it
fails on a later server. Other commands like BLPOP will likely never work when the keys are not on the same server.

Please note, that in some use-cases you can get all the atomicity guaranteed by a single redis server, when you use key
prefixes and an own hashing algorithm, so that you can map all keys that might be used together in the same multi key command
to a single redis server. (If you have two types of lists, "X" and "Y", it is unlikely, that you use this types mixed together
in a single BLPOP so you can put "X:*" on redis server 1 and "Y:*" on redis server 2)

## Status

This client is based on the initial release of a redis c++ client from https://github.com/Linkerist/redis-cpp.
It was changed to work with Redis 4.x. 
Please note, that this software has an experimental state.

API:
It is not guaranteed that the api from the initial 'fictorial' release will be continued. Generally the current api is not
stable and not well documented. Please have a look at the provided test cases (test_client.cpp) to see what is currently possible.

Any kind of feedback, suggestions and bug reports is very welcome.

## License

To be consistent with the redis community.
This client is licensed under the BSD 3(same license as redis). 

## Authors

- Linkerist <Linkerst at 163 dot com>
