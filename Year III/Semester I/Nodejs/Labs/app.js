import express from 'express';
import { GraphQLSchema } from 'graphql';
import queryType from './graphql/rootTypes/queryType.js';
import { createHandler } from 'graphql-http/lib/use/express';
import mutationType from './graphql/rootTypes/mutationType.js';
import jwt from 'jsonwebtoken';
import { JWT_SECRET } from './constants.js';

const schema = new GraphQLSchema({
  query: queryType,
  mutation: mutationType
});

const app = express();

const jwtMiddleware = (req, res, next) => {
  const token = req.headers.authorization?.replace("Bearer ", "");
  if (!token) {
    next();
    return;
  }
  try {
    const decodedPayload = jwt.verify(token, JWT_SECRET);
    req.user_id = decodedPayload.user_id;
    next();
  }
  catch (e) {
    console.log("Invalid token");
    next();
  }
};

app.all(
  "/graphql",
  jwtMiddleware,
  createHandler({
    schema: schema,
    context: req => ({ user_id: req.raw.user_id })
  })
);

export default app;