import asyncpg
import asyncio
import os
from dotenv import load_dotenv

load_dotenv()


async def run():
    conn = await asyncpg.connect(os.getenv('DB_URL'))

    await create_user(conn, 'pwat', 'password')
    await create_database(conn, 'test')
    await create_schema(conn, 'test_schema', 'pwat', 'test')
    await grant_access(conn, 'test_schema', 'pwat')
    await conn.close()

asyncio.run(run())


def escape_identifier(identifier):
    return '"' + identifier.replace('"', '""') + '"'


async def create_database(conn, name):
    exists = await conn.fetchval(
        "SELECT 1 FROM pg_database WHERE datname = $1", name
    )

    if not exists:
        safe_db = escape_identifier(name)
        await conn.execute(f"CREATE DATABASE {safe_db}")
        print(f"Database '{name}' created.")
    else:
        print(f"Database '{name}' already exists.")


async def create_user(conn, user, password):
    exists = await conn.fetchval(
        "SELECT 1 FROM pg_roles WHERE rolname = $1", user
    )

    if not exists:
        await conn.execute(
            "CREATE ROLE " + user + "WITH LOGIN PASSWORD $1", password
        )
        print(f"User '{user}' created.")

    else:
        print(f"User '{user}' already exists.")


async def create_schema(conn, schema, user, name):
    safe_s = escape_identifier(schema)
    safe_u = escape_identifier(user)
    safe_db = escape_identifier(name)

    await conn.execute(
        f"CREATE SCHEMA {safe_s} AUTHORIZATION {safe_u}"
    )

    await conn.execute(
        f"ALTER DATABASE {safe_db} SET search_path TO {safe_s}"
    )

    await conn.execute(
        f"GRANT USAGE ON SCHEMA {safe_s} TO {safe_u}"
    )

    await conn.execute(
        f"GRANT CREATE ON SCHEMA {safe_s} TO {safe_u}"
    )

    print(f"Schema '{schema}' in DB '{name}' created.")


async def grant_access(conn, schema, user):
    safe_s = escape_identifier(schema)
    safe_u = escape_identifier(user)

    await conn.execute(
        f"ALTER DEFAULT PRIVILEGES FOR ROLE {safe_u} IN SCHEMA {safe_s} "
        f"GRANT SELECT, INSERT, UPDATE, DELETE ON TABLES TO {safe_u}")

    await conn.execute(
        f"ALTER DEFAULT PRIVILEGES FOR ROLE {safe_u} IN SCHEMA {safe_s} "
        f"GRANT USAGE, SELECT, UPDATE ON SEQUENCES TO {safe_u}"
    )

    await conn.execute(
        f"ALTER USER {safe_u} WITH NOCREATEDB NOCREATEROLE"
    )

    print(f"Privileges granted for '{user}' in schema '{schema}'.")
