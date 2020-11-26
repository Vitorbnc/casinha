import asyncio
import websockets
import time
time.sleep(30) # wait 30 secs

async def hello(uri):
    async with websockets.connect(uri) as websocket:
        await websocket.send("{btn:0xaf}")

asyncio.get_event_loop().run_until_complete(
    hello('ws://192.168.1.3:81'))