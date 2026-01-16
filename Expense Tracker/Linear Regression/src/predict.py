import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression
import json
import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: predict.py <input_csv> <output_json>")
        return

    input_csv = sys.argv[1]
    output_json = sys.argv[2]

    # Read monthly totals from CSV
    df = pd.read_csv(input_csv)
    df = df.sort_values("month").reset_index(drop=True)

    if df.empty:
        result = {"error": "No data"}
        json.dump(result, open(output_json, "w"))
        return

    X = np.arange(len(df)).reshape(-1, 1)
    y = df["total"].values
    import matplotlib.pyplot as plt
    plt.plot(df['month'], df['total'], marker='o')
    plt.show()
    model = LinearRegression()
    model.fit(X, y)

    pred = float(model.predict([[len(df)]])[0])
    rmse = np.sqrt(np.mean((model.predict(X) - y) ** 2))
    rmse_percent = (rmse / np.mean(y)) * 100

    # result = {
    #     "train_months": len(df),
    #     "rmse_percent": round(rmse_percent, 2),
    #     "predicted_next_total": round(pred, 2)
    # }

    result = round(pred, 2)

    json.dump(result, open(output_json, "w"))

if __name__ == "__main__":
    main()
