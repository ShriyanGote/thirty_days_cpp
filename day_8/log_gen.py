import random, datetime

levels = ["INFO", "WARN", "ERROR", "DEBUG"]
messages = ["user login", "db query", "cache miss", "request timeout", "payment processed"]

for i in range(4):
    with open(f"logs/file_{i}.log", "w") as f:
        t = datetime.datetime(2024, 1, 15, 0, 0, 0)
        for _ in range(10000):
            t += datetime.timedelta(seconds=random.randint(0, 2))
            lvl = random.choices(levels, weights=[60, 20, 10, 10])[0]
            lat = random.randint(5, 2000)
            msg = random.choice(messages)
            f.write(f"[{t.strftime('%Y-%m-%d %H:%M:%S')}] {lvl:<5} latency={lat}ms \"{msg}\"\n")