def parse(line):

    try:

        data = line.split(",")

        return {

            "temp": float(data[0]),
            "pressure": float(data[1]),
            "altitude": float(data[2]),

            "ax": float(data[3]),
            "ay": float(data[4]),
            "az": float(data[5]),

            "gx": float(data[6]),
            "gy": float(data[7]),
            "gz": float(data[8]),

            "mq2": data[9]

        }

    except:

        return None